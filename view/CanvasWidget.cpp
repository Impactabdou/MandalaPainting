#include "CanvasWidget.h"
#include <QPainter>
#include <QPixmap>
#include <QCursor>
#include <QDebug> // Added to help us find the error!

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent) {
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

    painter.fillRect(rect(), Qt::white);

    QPen pen(QColor(210, 210, 210));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawRoundedRect(rect().adjusted(1, 1, -2, -2), 8, 8);
}
