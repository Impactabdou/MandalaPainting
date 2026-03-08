#include "linepreview.h"
#include <QPainter>

LinePreview::LinePreview(QWidget* parent) : QFrame(parent) {
    setMinimumSize(24, 24);
}

void LinePreview::setPenColor(const QColor& color) {
    _color = color;
    update();
}

void LinePreview::setPenWidth(int width) {
    _width = width;
    update();
}

void LinePreview::paintEvent(QPaintEvent* event) {
    QFrame::paintEvent(event);

    QPainter painter(this);
    // Make the circle smooth
    painter.setRenderHint(QPainter::Antialiasing);

    // 1. Fill the background white
    painter.fillRect(rect().adjusted(1, 1, -1, -1), Qt::white);

    // 2. Draw the dot
    painter.setPen(Qt::NoPen); // No outline around the dot
    painter.setBrush(_color);  // Fill with the selected color

    QPoint center = rect().center();

    // Draw the circle.
    // minimum dot size of 1px
    int radius = std::max(1, _width / 2);
    painter.drawEllipse(center, radius, radius);
}
