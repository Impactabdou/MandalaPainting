#include "CanvasWidget.h"


#include <QPainter>
#include <QPixmap>
#include <QCursor>
#include <QDebug>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent), gridDrawer(new GridDrawer(0)), canvasHeight(400), canvasWidth(400) {
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
    QRect canvasRect(
        (width() - canvasWidth) / 2,
        (height() - canvasHeight) / 2,
        canvasWidth,
        canvasHeight
    );
    painter.fillRect(canvasRect, Qt::white);

    QPen pen(QColor(210, 210, 210));
    pen.setWidth(2);
    painter.setPen(pen);


    painter.drawRoundedRect(canvasRect.adjusted(1, 1, -2, -2), 8, 8);
    painter.save();
    painter.setClipRect(canvasRect);
    gridDrawer->drawGrid(painter, canvasRect);
    painter.restore();
}

void CanvasWidget::setCanvasSize(int width, int height) {
    canvasWidth = width;
    canvasHeight = height;
    update();
}

void CanvasWidget::setSlices(int slices) {
    if (slices < 2) {
        gridDrawer->setSlices(0);
        update();
        return;
    }
    gridDrawer->setSlices(slices);
    update();
}

void CanvasWidget::setGridOpacity(int width) {
    gridDrawer->setGridOpacity(width);
    update();
}

