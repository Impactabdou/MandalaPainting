#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include <QWidget>
#include "GridDrawer.h"
#include "MouseController.h"
#include  "model/MandalaModel.h"
#include <QUndoStack>
#include "model/Stroke.h"
#include <QVector>

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


    void setPenColor(const QColor &color) { _currColor = color; };

    [[nodiscard]] int getSlices() const { return _mandalaModel.getSlices(); }

    void saveToFile(const QString &filePath);

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
    QVector<Stroke> _paintedStrokes;
    int _penWidth;
    QUndoStack *_undoStack;
    QVector<Stroke> _currentStrokeSegments;
    QColor _currColor = Qt::black;


    void repaintMandala();
};
#endif
