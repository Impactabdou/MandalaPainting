#pragma once
#include <vector>

class GridDrawerModel {
public:
    ~GridDrawerModel() = default;

    static void computeGridPositions(std::vector<std::pair<double, double> > &coordinates, double diagonal, int centerX,
                                     int centerY,
                                     int slices);
};
