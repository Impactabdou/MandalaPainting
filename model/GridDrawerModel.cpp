#include "GridDrawerModel.h"
#include <cmath>

void GridDrawerModel::computeGridPositions(QVector<QPointF> &coordinates, const double diagonal,
                                           const int centerX,
                                           const int centerY,
                                           const int slices) {
    if (slices <= 0) {
        return;
    }
    const double radius = std::sqrt(diagonal) / 2.0;
    for (int i = 0; i < slices; ++i) {
        const double angle = (2 * M_PI / slices) * i;
        QPointF point = {
            centerX + radius * std::cos(angle), centerY + radius * std::sin(angle)
        };
        coordinates.append({point.x(), point.y()});
    }
}
