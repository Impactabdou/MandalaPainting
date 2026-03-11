#ifndef GRIDDRAWER_H
#define GRIDDRAWER_H
#include <QPainter>
#include <QObject>
#include <QRect>

class GridDrawer : public QObject {
    Q_OBJECT

public:
    explicit GridDrawer(int slices = 0, QObject *parent = nullptr);

    void drawGrid(QPainter &painter, const QRect &area) const;

    void setSlices(const int slices) { _numberOfSlices = slices; }

    void setGridOpacity(const int width) { _gridOpacity = width; }

private:
    int _numberOfSlices;
    int _gridOpacity = 90;
};
#endif
