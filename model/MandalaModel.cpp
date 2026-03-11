#include "MandalaModel.h"
#include <cmath>
#include <algorithm>

MandalaModel::MandalaModel() : _slices(0), _mirrorEffect(false), _max(0) {
}

void MandalaModel::draw(const QPoint lastpos,
                        const QPoint currentpos,
                        const QColor &color,
                        const int width) {
    _strokes.append({lastpos, currentpos, color, width});
    _max = _strokes.size() - 1;
}

void MandalaModel::clear() {
    _strokes.clear();
    _max = -1;
}

void MandalaModel::addStrokeSegments(const QVector<Stroke> &segments) {
    _strokes.append(segments);
    _max = _strokes.size() - 1;
}

void MandalaModel::removeLastSegments(const int count) {
    if (count <= _strokes.size()) {
        _strokes.resize(_strokes.size() - count);
        _max = _strokes.size() - 1;
    }
}

QVector<Stroke> MandalaModel::getStrokes() const {
    const int endIndex = std::min(_max + 1, static_cast<int>(_strokes.size()));
    return _strokes.mid(0, endIndex);
}

QVector<QPair<QPointF, QPointF> > MandalaModel::generateMandalaLines(
    const QPointF &p1,
    const QPointF &p2,
    const QPointF &center
) const {
    QVector<QPair<QPointF, QPointF> > lines;

    if (_slices <= 0) {
        return lines;
    }

    const double angleStep = 2 * M_PI / _slices;

    const QPointF translatedP1 = translationToCenter(p1, center);
    const QPointF translatedP2 = translationToCenter(p2, center);

    for (int i = 0; i < _slices; i++) {
        const double angle = i * angleStep;

        QPointF rotatedP1 = rotatePoint(translatedP1, angle);
        QPointF rotatedP2 = rotatePoint(translatedP2, angle);


        QPointF inversedTranslatedP1 = translationFromCenter(rotatedP1, center);
        QPointF inversedTranslatedP2 = translationFromCenter(rotatedP2, center);
        lines.append({inversedTranslatedP1, inversedTranslatedP2});

        if (_mirrorEffect) {
            QPointF mirrorP1 = translationFromCenter(QPointF(-rotatedP1.x(), rotatedP1.y()), center);
            QPointF mirrorP2 = translationFromCenter(QPointF(-rotatedP2.x(), rotatedP2.y()), center);
            lines.append({mirrorP1, mirrorP2});
        }
    }
    return lines;
}

QPointF MandalaModel::rotatePoint(const QPointF &p, const double angle) {
    const double cosAngle = std::cos(angle);
    const double sinAngle = std::sin(angle);
    const double x = p.x() * cosAngle - p.y() * sinAngle;
    const double y = p.x() * sinAngle + p.y() * cosAngle;
    return {x, y};
}
