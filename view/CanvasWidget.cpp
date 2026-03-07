#include "CanvasWidget.h"


#include <QPainter>
#include <QPixmap>
#include <QCursor>
#include <QDebug>
#include <QMouseEvent>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent), _gridDrawer(2), _canvasHeight(400), _canvasWidth(400), _penWidth(3) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPixmap cursorPixmap("://default_pencil.png");

    if (cursorPixmap.isNull()) {
        qDebug() << "Ressources Error: could not locate the pencil canvas";
    } else {
        QPixmap scaledPixmap = cursorPixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QCursor customCursor(scaledPixmap, 0, 0);
        this->setCursor(customCursor);
    }
}


void CanvasWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect canvasRect(
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

    QPen drawPen(Qt::magenta);
    drawPen.setJoinStyle(Qt::RoundJoin);
    drawPen.setWidth(_penWidth);
    drawPen.setCapStyle(Qt::RoundCap);
    painter.setPen(drawPen);

    for (const auto &stroke: _paintedStrokes) {
        painter.drawLine(stroke.first, stroke.second);
    }

    painter.restore();
}

void CanvasWidget::setCanvasSize(int width, int height) {
    _canvasWidth = width;
    _canvasHeight = height;
    update();
}

void CanvasWidget::setSlices(int slices) {
    if (slices < 2) {
        _gridDrawer.setSlices(0);
    }
    _gridDrawer.setSlices(slices);
    _mandalaModel.setSlices(slices);
    repaintMandala();
    update();
}

void CanvasWidget::setGridOpacity(int width) {
    _gridDrawer.setGridOpacity(width);
    update();
}

void CanvasWidget::clear() {
    _strokes.clear();
    _paintedStrokes.clear();
    update();
}

void CanvasWidget::setMirror(bool mirror) {
    _mandalaModel.setMirrorEffect(mirror);
    repaintMandala();
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event) {
    _mouseController.handlePress(event);
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event) {
    _mouseController.handleMove(event);

    QRect canvasRect(
        (width() - _canvasWidth) / 2,
        (height() - _canvasHeight) / 2,
        _canvasWidth,
        _canvasHeight
    );

    if (!_mouseController.isDrawing()) { return; }
    if (!canvasRect.contains(event->pos())) { return; }

    QPoint lastpos = _mouseController.getLastPosition();
    QPoint currentpos = _mouseController.getCurrentPosition();

    _strokes.emplace_back(lastpos, currentpos);
    _mouseController.setLastPosition(currentpos);
    repaintMandala();
    update();
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event) {
    _mouseController.handleRelease(event);
}

void CanvasWidget::repaintMandala() {
    _paintedStrokes.clear();
    QRect canvasRect(
        (width() - _canvasWidth) / 2,
        (height() - _canvasHeight) / 2,
        _canvasWidth,
        _canvasHeight
    );
    const QPoint center(canvasRect.center());

    for (const auto &stroke: _strokes) {
        auto mandalaLines = _mandalaModel.generateMandalaLines(toPoint(stroke.first)
                                                               , toPoint(stroke.second), toPoint(center));

        for (const auto &line: mandalaLines) {
            _paintedStrokes.emplace_back(
                QPoint(static_cast<int>(line.first.x), static_cast<int>(line.first.y)),
                QPoint(static_cast<int>(line.second.x), static_cast<int>(line.second.y))
            );
        }
    }
}
