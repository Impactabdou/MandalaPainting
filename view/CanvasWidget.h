#pragma once
#include <QWidget>
#include "GridDrawer.h"
#include "MouseController.h"
#include  "model/MandalaModel.h"
#include <QUndoStack>
#include "model/Stroke.h"

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

    void setPenColor(QColor color) { _currColor = color;};

    int getSlices() const { return _mandalaModel.getSlices(); }

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
    MandalaModel _mandalaModel;
    std::vector<Stroke> _paintedStrokes;
    int _penWidth;
    QUndoStack* _undoStack;
    std::vector<Stroke> _currentStrokeSegments;
    QColor _currColor = Qt::black;

    static Point toPoint(const QPoint &point) {
        return {static_cast<double>(point.x()), static_cast<double>(point.y())};
    }

    void repaintMandala();
};
