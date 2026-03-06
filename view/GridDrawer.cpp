#include "GridDrawer.h"
#include <vector>
#include <QDebug>

#include "model/GridDrawerModel.h"

GridDrawer::GridDrawer(int slices) : _numberOfSlices(slices) {
}

void GridDrawer::drawGrid(QPainter &painter, const QRect &area) {
    painter.setRenderHints(QPainter::Antialiasing);
    QPen pen(QColor(50, 50, 50, gridOpacity));
    pen.setStyle(Qt::DotLine);
    pen.setWidth(4);
    painter.setPen(pen);


    std::vector<std::pair<int, int> > coordinates;
    double radius = area.width() * area.width() + area.height() * area.height();
    GridDrawerModel::computeGridPositions(coordinates, radius, area.center().x(), area.center().y(), _numberOfSlices);
#ifdef QT_DEBUG
    for (auto &coord: coordinates) {
        qDebug() << "Coordinate: (" << coord.first << ", " << coord.second << ")";
    }
#endif

    for (int i = 0; i < _numberOfSlices; ++i) {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        painter.drawLine(area.center().x(), area.center().y(), x, y);
    }
}
