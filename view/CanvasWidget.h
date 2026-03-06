#pragma once
#include <QWidget>
#include "GridDrawer.h"

class CanvasWidget : public QWidget {
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);

    void setCanvasSize(int width, int height);

    void setSlices(int slices);

    void setGridOpacity(int width);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    GridDrawer *gridDrawer;
    int canvasHeight;
    int canvasWidth;
};
