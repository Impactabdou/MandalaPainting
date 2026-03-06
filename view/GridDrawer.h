#pragma once
#include <QPainter>
#include <QRect>

class GridDrawer {
public:
    explicit GridDrawer(int slices = 0);

    void drawGrid(QPainter &painter, const QRect &area);

    void setSlices(int slices) { _numberOfSlices = slices; }

    void setGridOpacity(int width) { _gridOpacity = width; }

private:
    int _numberOfSlices;
    int _gridOpacity = 90;
};
