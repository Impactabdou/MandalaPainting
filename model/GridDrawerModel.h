#ifndef GRIDDRAWERMODEL_H
#define GRIDDRAWERMODEL_H
#include <QPointF>
#include <QObject>


class GridDrawerModel : public QObject {
    Q_OBJECT

public:
    ~GridDrawerModel() override = default;

    explicit GridDrawerModel(QObject *parent = nullptr) : QObject(parent) {
    }

    static void computeGridPositions(QVector<QPointF> &coordinates, double diagonal, int centerX,
                                     int centerY,
                                     int slices);
};

#endif // GRIDDRAWERMODEL_H
