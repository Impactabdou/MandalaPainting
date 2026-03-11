#ifndef STROKE_H
#define STROKE_H
#include <QPoint>
#include <QColor>

struct Stroke {
    QPointF p1;
    QPointF p2;
    QColor color;
    int width;
};
#endif
