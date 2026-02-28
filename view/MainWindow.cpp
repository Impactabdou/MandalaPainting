#include "MainWindow.h"
#include "CanvasWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    CanvasWidget *canvas = new CanvasWidget(ui.canvasFrame);

    ui.canvasLayout->setContentsMargins(0, 0, 0, 0);
    ui.canvasLayout->setSpacing(0);

    ui.canvasLayout->addWidget(canvas);
}
