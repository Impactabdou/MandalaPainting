#ifndef  MANDALAMODEL_H
#define MANDALAMODEL_H
#include <vector>
#include "Point.h"
#include "qpoint.h"
#include "Stroke.h"
class MandalaModel {
public:
    MandalaModel();

    void setSlices(int slices) { _slices = slices; }

    std::vector<std::pair<Point, Point> > generateMandalaLines(const Point &p1, const Point &p2,
                                                               const Point &center);

    void setMirrorEffect(const bool mirrorEffectActived) { _mirrorEffect = mirrorEffectActived; }

    void draw(const QPoint lastpos,const QPoint currentpos,const QColor& color,int width);

    void undo();

    void redo();

    void addStrokeSegments(const std::vector<Stroke>& segments);

    void removeLastSegments(int count);
    void clear();

    std::vector<Stroke> getStrokes();

    int getSlices() const { return _slices; }


private:
    int _slices;
    bool _mirrorEffect;
    std::vector<Stroke> _strokes;
    int _max;



    static Point translationToCenter(const Point &p, const Point &center) {
        return {p.x - center.x, p.y - center.y};
    }

    static Point translationFromCenter(const Point &p, const Point &center) {
        return {p.x + center.x, p.y + center.y};
    }

    static Point rotatePoint(const Point &p, double angle);
};

#endif
