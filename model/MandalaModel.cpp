#include "MandalaModel.h"
#include <cmath>

MandalaModel::MandalaModel() : _slices(0), _mirrorEffect(false),_currentIdx(0) {
}

std::vector<std::pair<Point, Point> > MandalaModel::generateMandalaLines(
    const Point &p1,
    const Point &p2,
    const Point &center
) {
    std::vector<std::pair<Point, Point> > lines;

    if (_slices <= 0) {
        return lines;
    }

    const double angleStep = 2 * M_PI / _slices;

    const Point translatedP1 = translationToCenter(p1, center);
    const Point translatedP2 = translationToCenter(p2, center);

    for (int i = 0; i < _slices; i++) {
        const double angle = i * angleStep;

        Point rotatedP1 = rotatePoint(translatedP1, angle);
        Point rotatedP2 = rotatePoint(translatedP2, angle);


        Point inversedTranslatedP1 = translationFromCenter(rotatedP1, center);
        Point inversedTranslatedP2 = translationFromCenter(rotatedP2, center);
        lines.emplace_back(inversedTranslatedP1, inversedTranslatedP2);

        if (_mirrorEffect) {
            Point mirrorP1 = translationFromCenter(-rotatedP1, center);
            Point mirrorP2 = translationFromCenter(-rotatedP2, center);
            lines.emplace_back(mirrorP1, mirrorP2);
        }
    }
    _allLines.append(lines);
    return lines;
}

Point MandalaModel::rotatePoint(const Point &p, const double angle) {
    const double cosAngle = std::cos(angle);
    const double sinAngle = std::sin(angle);
    const double x = p.x * cosAngle - p.y * sinAngle;
    const double y = p.x * sinAngle + p.y * cosAngle;
    return {x, y};
}
