#ifndef STROKE_H
#define STROKE_H
#include <QPoint>
#include <QColor>

struct Stroke {
    QPoint p1;
    QPoint p2;
    QColor color;
    int width;
};
#endif
