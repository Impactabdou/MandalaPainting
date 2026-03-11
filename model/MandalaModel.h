#ifndef  MANDALAMODEL_H
#define MANDALAMODEL_H
#include "Stroke.h"
#include <QVector>
#include <QPointF>
#include <QPair>
#include <QObject>

class MandalaModel : public QObject {
    Q_OBJECT

public:
    MandalaModel();

    void setSlices(const int slices) { _slices = slices; }

    [[nodiscard]] QVector<QPair<QPointF, QPointF> > generateMandalaLines(const QPointF &p1, const QPointF &p2,
                                                                         const QPointF &center) const;

    void setMirrorEffect(const bool mirrorEffectActived) { _mirrorEffect = mirrorEffectActived; }

    void draw(QPoint lastpos, QPoint currentpos, const QColor &color, int width);

    void addStrokeSegments(const QVector<Stroke> &segments);

    void removeLastSegments(int count);

    void clear();

    [[nodiscard]] QVector<Stroke> getStrokes() const;

    [[nodiscard]] int getSlices() const { return _slices; }

private:
    int _slices;
    bool _mirrorEffect;
    QVector<Stroke> _strokes;
    int _max;


    static QPointF translationToCenter(const QPointF &p, const QPointF &center) {
        return {p.x() - center.x(), p.y() - center.y()};
    }

    static QPointF translationFromCenter(const QPointF &p, const QPointF &center) {
        return {p.x() + center.x(), p.y() + center.y()};
    }

    static QPointF rotatePoint(const QPointF &p, double angle);
};

#endif
