#pragma once
#include <vector>
#include "Point.h"

class MandalaModel {
public:
    MandalaModel();

    void setSlices(int slices) { _slices = slices; }

    std::vector<std::pair<Point, Point> > generateMandalaLines(const Point &p1, const Point &p2,
                                                               const Point &center) const;

    void setMirrorEffect(const bool mirrorEffectActived) { _mirrorEffect = mirrorEffectActived; }

private:
    int _slices;
    bool _mirrorEffect;

    static Point translationToCenter(const Point &p, const Point &center) {
        return {p.x - center.x, p.y - center.y};
    }

    static Point translationFromCenter(const Point &p, const Point &center) {
        return {p.x + center.x, p.y + center.y};
    }

    static Point rotatePoint(const Point &p, double angle);
};
