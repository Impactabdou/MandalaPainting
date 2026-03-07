#pragma once
#include <vector>
#include "Point.h"
#include "QList"
#include "qpoint.h"

class MandalaModel {
public:
    MandalaModel();

    void setSlices(int slices) { _slices = slices; }

    std::vector<std::pair<Point, Point> > generateMandalaLines(const Point &p1, const Point &p2,
                                                               const Point &center);

    void setMirrorEffect(const bool mirrorEffectActived) { _mirrorEffect = mirrorEffectActived; }

    void draw(const QPoint lastpos,
              const QPoint currentpos);

    void undo();

    void redo();

    void addStrokeSegments(const std::vector<std::pair<QPoint, QPoint>>& segments);
    void removeLastSegments(int count);
    void clear();

    std::vector<std::pair<QPoint, QPoint>> getStrokes();


private:
    int _slices;
    bool _mirrorEffect;
    std::vector<std::pair<QPoint, QPoint>> _strokes;
    int _max;



    static Point translationToCenter(const Point &p, const Point &center) {
        return {p.x - center.x, p.y - center.y};
    }

    static Point translationFromCenter(const Point &p, const Point &center) {
        return {p.x + center.x, p.y + center.y};
    }

    static Point rotatePoint(const Point &p, double angle);
};
