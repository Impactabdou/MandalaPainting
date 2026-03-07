#include "GridDrawerModel.h"
#include <cmath>

#include "Point.h"

void GridDrawerModel::computeGridPositions(std::vector<std::pair<double,double> > &coordinates, const double diagonal,
                                           const int centerX,
                                           const int centerY,
                                           const int slices) {
    if (slices <= 0) {
        return;
    }
    for (int i = 0; i < slices; ++i) {
        const double angle = (2 * M_PI / slices) * i;
        Point point = {centerX + sqrt(diagonal) / 2.0 * cos(angle), centerY + sqrt(diagonal) / 2.0 * sin(angle)};
        coordinates.emplace_back(point.x, point.y);
    }
}
