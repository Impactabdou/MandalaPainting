#include "CanvasWidget.h"
#include "model/drawcommand.h"
#include <QUndoStack>
#include <QPainter>
#include <QPixmap>
#include <QCursor>
#include <QDebug>
#include <QMouseEvent>
#include "model/SliceCommand.h"
#include <QFileDialog>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent), _gridDrawer(2), _canvasHeight(400), _canvasWidth(400), _penWidth(3) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    _undoStack = new QUndoStack(this);

    _mandalaModel.setSlices(2);

    QPixmap cursorPixmap("://default_pencil.png");

    if (cursorPixmap.isNull()) {
        qDebug() << "Ressources Error: could not locate the pencil canvas";
    } else {
        QPixmap scaledPixmap = cursorPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QCursor customCursor(scaledPixmap, 8, -28);
        this->setCursor(customCursor);
    }
}

void CanvasWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    const QRect canvasRect(
        (width() - _canvasWidth) / 2,
        (height() - _canvasHeight) / 2,
        _canvasWidth,
        _canvasHeight
    );

    painter.fillRect(canvasRect, Qt::white);

    QPen borderPen(QColor(210, 210, 210));
    borderPen.setWidth(6);
    painter.setPen(borderPen);
    painter.drawRoundedRect(canvasRect.adjusted(1, 1, -2, -2), 8, 8);

    painter.save();
    painter.setClipRect(canvasRect);

    _gridDrawer.drawGrid(painter, canvasRect);

    for (const auto &stroke: _paintedStrokes) {
        QPen pen(stroke.color);
        pen.setWidth(stroke.width);
        pen.setJoinStyle(Qt::RoundJoin);
        pen.setCapStyle(Qt::RoundCap);

        painter.setPen(pen);
        painter.drawLine(stroke.p1, stroke.p2);
    }

    painter.restore();
}

void CanvasWidget::setCanvasSize(const int width, const int height) {
    _canvasWidth = width;
    _canvasHeight = height;
    update();
}

void CanvasWidget::setSlices(const int slices) {
    if (slices < 2) {
        _gridDrawer.setSlices(0);
    }
    _gridDrawer.setSlices(slices);
    _undoStack->push(new SliceCommand(&_mandalaModel, slices));
    _gridDrawer.setSlices(_mandalaModel.getSlices());
    repaintMandala();
    update();
}

void CanvasWidget::setGridOpacity(const int width) {
    _gridDrawer.setGridOpacity(width);
    update();
}

void CanvasWidget::clear() {
    _paintedStrokes.clear();
    _undoStack->clear();
    _mandalaModel.clear();
    update();
}

void CanvasWidget::setMirror(const bool mirror) {
    _mandalaModel.setMirrorEffect(mirror);
    repaintMandala();
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    _mouseController.handlePress(event);
    _currentStrokeSegments.clear();
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    _mouseController.handleMove(event);

    const QRect canvasRect(
        (width() - _canvasWidth) / 2,
        (height() - _canvasHeight) / 2,
        _canvasWidth,
        _canvasHeight
    );

    if (!_mouseController.isDrawing()) { return; }
    if (!canvasRect.contains(event->pos())) { return; }

    const QPoint lastpos = _mouseController.getLastPosition();
    const QPoint currentpos = _mouseController.getCurrentPosition();

    Stroke segment;
    segment.p1 = lastpos;
    segment.p2 = currentpos;
    segment.width = _penWidth;
    _currentStrokeSegments.push_back(segment);

    _mandalaModel.draw(lastpos, currentpos, _currColor, _penWidth);
    _mouseController.setLastPosition(currentpos);
    repaintMandala();
    update();
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
    _mouseController.handleRelease(event);

    if (!_currentStrokeSegments.empty()) {
        _mandalaModel.removeLastSegments(_currentStrokeSegments.size());

        auto *cmd = new DrawCommand(&_mandalaModel, _currentStrokeSegments);
        _undoStack->push(cmd);

        _currentStrokeSegments.clear();

        repaintMandala();
        update();
    }
}


void CanvasWidget::saveToFile(const QString &filePath) {
    const QPixmap pixmap = this->grab();
    QString extension;
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Mandala",
        filePath,
        "PNG Image (*.png);;JPEG Image (*.jpg)",
        &extension
    );

    if (fileName.isEmpty()) {
        return;
    }
    if (!fileName.contains(".")) {
        if (extension.contains("JPEG")) {
            fileName += ".jpg";
        } else {
            fileName += ".png";
        }
    }
    const bool fileSaved = pixmap.save(fileName);
    if (!fileSaved) {
        qDebug() << "Error: Could not save the file.";
    }
}

void CanvasWidget::repaintMandala() {
    _paintedStrokes.clear();
    const QRect canvasRect(
        (width() - _canvasWidth) / 2,
        (height() - _canvasHeight) / 2,
        _canvasWidth,
        _canvasHeight
    );
    const QPoint center(canvasRect.center());

    auto strokes = _mandalaModel.getStrokes();

    for (const auto &stroke: strokes) {
        auto mandalaLines = _mandalaModel.generateMandalaLines(stroke.p1, stroke.p2, center);

        int numLines = mandalaLines.size();
        int sliceIndex = 0;

        for (const auto &line: mandalaLines) {
            Stroke s;
            s.p1 = QPointF(line.first.x(), line.first.y());
            s.p2 = QPointF(line.second.x(), line.second.y());
            s.width = stroke.width;

            if (_is_colorful && numLines > 0) {
                int baseHue = stroke.color.hue();
                if (baseHue == -1) { baseHue = 0; }

                int hueStep = 360 / numLines;
                int currentHue = (baseHue + (sliceIndex * hueStep)) % 360;

                s.color = QColor::fromHsv(currentHue, 255, 255);
            } else {
                s.color = stroke.color;
            }

            _paintedStrokes.push_back(s);
            sliceIndex++;
        }
    }
}

void CanvasWidget::undo() {
    _undoStack->undo();
    _gridDrawer.setSlices(_mandalaModel.getSlices());
    repaintMandala();
    update();
}

void CanvasWidget::redo() {
    _undoStack->redo();
    _gridDrawer.setSlices(_mandalaModel.getSlices());
    repaintMandala();
    update();
}
