#pragma once
#include <QWidget>
#include "GridDrawer.h"
#include "MouseController.h"
#include  "model/MandalaModel.h"

class CanvasWidget : public QWidget {
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);


    void setCanvasSize(int width, int height);

    void setSlices(int slices);

    void setGridOpacity(int width);

    void clear();

    void setMirror(bool mirror);

    void setPenWidth(const int width) { _penWidth = width; }

    void undo();

    void redo();

    void repaintFromModel();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    GridDrawer _gridDrawer;
    int _canvasHeight;
    int _canvasWidth;
    MouseController _mouseController;
    std::vector<std::pair<QPoint, QPoint> > _strokes;
    MandalaModel _mandalaModel;
    std::vector<std::pair<QPoint, QPoint> > _paintedStrokes;
    int _penWidth;

    static Point toPoint(const QPoint &point) {
        return {static_cast<double>(point.x()), static_cast<double>(point.y())};
    }

    void repaintMandala();
};
