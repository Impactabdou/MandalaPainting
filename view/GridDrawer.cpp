#include "GridDrawer.h"
#include <QDebug>

#include "model/GridDrawerModel.h"

GridDrawer::GridDrawer(const int slices, QObject *parent) : QObject(parent), _numberOfSlices(slices) {
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

    const QPoint center = area.center();
    QVector<QPointF> coordinates;
    const double diagonal = area.width() * area.width() + area.height() * area.height();
    GridDrawerModel::computeGridPositions(
        coordinates,
        diagonal,
        center.x(),
        center.y(),
        _numberOfSlices
    );

    for (const auto &coordinate: coordinates) {
        painter.drawLine(
            center, coordinate.toPoint()
        );
    }
}
