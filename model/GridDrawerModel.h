#pragma once
#include <vector>

class GridDrawerModel {
public:
    ~GridDrawerModel() = default;

    static void computeGridPositions(std::vector<std::pair<int, int> > &coordinates, double radius, int centerX,
                                     int centerY,
                                     int slices);
};
