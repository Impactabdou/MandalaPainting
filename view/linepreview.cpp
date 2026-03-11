#include "linepreview.h"
#include <QPainter>

LinePreview::LinePreview(QWidget* parent) : QFrame(parent) {
    setMinimumSize(24, 24);
}

void LinePreview::setPenColor(const QColor& color) {
    _color = color;
    update();
}

void LinePreview::setPenWidth(const int width) {
    _width = width;
    update();
}

void LinePreview::paintEvent(QPaintEvent* event) {
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect().adjusted(1, 1, -1, -1), Qt::white);

    painter.setPen(Qt::NoPen); // No outline around the dot
    painter.setBrush(_color);  // Fill with the selected color

    const QPoint center = rect().center();

    int radius = std::max(1, _width / 2);
    painter.drawEllipse(center, radius, radius);
}
