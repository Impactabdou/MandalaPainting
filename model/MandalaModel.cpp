#include "MandalaModel.h"
#include <cmath>

MandalaModel::MandalaModel() : _slices(0) {
}

std::vector<std::pair<QPoint, QPoint> > MandalaModel::generateMandalaLines(
    const QPoint &p1,
    const QPoint &p2,
    const QPoint &center
) {
    std::vector<std::pair<QPoint, QPoint> > lines;

    if (_slices <= 0) {
        return lines;
    }

    double angleStep = 2 * M_PI / _slices;

    double x1 = p1.x() - center.x();
    double y1 = p1.y() - center.y();

    double x2 = p2.x() - center.x();
    double y2 = p2.y() - center.y();

    for (int i = 0; i < _slices; i++) {
        double angle = i * angleStep;

        double rotationx1 = x1 * cos(angle) - y1 * sin(angle);
        double rotationy1 = x1 * sin(angle) + y1 * cos(angle);

        double rotationx2 = x2 * cos(angle) - y2 * sin(angle);
        double rotationy2 = x2 * sin(angle) + y2 * cos(angle);

        QPoint rotatedP1(rotationx1 + center.x(), rotationy1 + center.y());
        QPoint rotatedP2(rotationx2 + center.x(), rotationy2 + center.y());
        lines.push_back({rotatedP1, rotatedP2});

        if (_mirror) {
            double mx1 = -rotationx1;
            double my1 = rotationy1;

            double mx2 = -rotationx2;
            double my2 = rotationy2;

            QPoint mirrorP1(mx1 + center.x(), my1 + center.y());
            QPoint mirrorP2(mx2 + center.x(), my2 + center.y());

            lines.push_back({mirrorP1, mirrorP2});
        }
    }
    return lines;
}
