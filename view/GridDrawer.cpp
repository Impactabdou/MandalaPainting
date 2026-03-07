#include "GridDrawer.h"
#include <vector>
#include <QDebug>

#include "model/GridDrawerModel.h"

GridDrawer::GridDrawer(const int slices) : _numberOfSlices(slices) {
}

void GridDrawer::drawGrid(QPainter &painter, const QRect &area) const {
    if (_numberOfSlices <= 0) {
        return;
    }
    painter.setRenderHints(QPainter::Antialiasing);

    QPen pen(QColor(50, 50, 50, _gridOpacity));
    pen.setStyle(Qt::DotLine);
    pen.setWidth(4);
    painter.setPen(pen);


    std::vector<std::pair<double, double> > coordinates;
    double diagonal = area.width() * area.width() + area.height() * area.height();
    GridDrawerModel::computeGridPositions(
        coordinates,
        diagonal,
        area.center().x(),
        area.center().y(),
        _numberOfSlices
    );

    for (const auto &coordinate: coordinates) {
        painter.drawLine(
            area.center().x(),
            area.center().y(),
            static_cast<int>(coordinate.first),
            static_cast<int>(coordinate.second)
        );
    }
}
