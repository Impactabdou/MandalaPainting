#include "CanvasWidget.h"
#include <QPainter>

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CanvasWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    painter.fillRect(rect(), Qt::white);

    QPen pen(QColor(210, 210, 210));
    pen.setWidth(2);
    painter.setPen(pen);

    painter.drawRoundedRect(rect().adjusted(1, 1, -2, -2), 8, 8);
}
