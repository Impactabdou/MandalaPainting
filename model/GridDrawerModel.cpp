#include "GridDrawerModel.h"
#include <cmath>

void GridDrawerModel::computeGridPositions(std::vector<std::pair<int, int> > &coordinates, double radius, int centerX,
                                           int centerY,
                                           int slices) {
    for (int i = 0; i < slices; ++i) {
        double angle = (2 * M_PI / slices) * i;
        int x = centerX + sqrt(radius) / 2.0 * cos(angle);
        int y = centerY + sqrt(radius) / 2.0 * sin(angle);
        coordinates.push_back({x, y});
    }
}
