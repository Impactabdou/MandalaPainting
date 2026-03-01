#include "MainWindow.h"
#include "CanvasWidget.h"
#include <QPixmap>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    CanvasWidget *canvas = new CanvasWidget(ui.canvasFrame);

    ui.canvasLayout->setContentsMargins(0, 0, 0, 0);
    ui.canvasLayout->setSpacing(0);

    ui.canvasLayout->addWidget(canvas);

    // default color at start

    QPixmap colorSquare(16,16);

    QColor chosenColor = Qt::black;

    colorSquare.fill(chosenColor);

    ui.colorSelectBtn->setIcon(QIcon(colorSquare));

}


void MainWindow::on_colorSelectBtn_clicked()
{
    QColor chosenColor = QColorDialog::getColor(Qt::white, this, "Choose Color");

    if (chosenColor.isValid()) {
        QPixmap colorSquare(16, 16);

        colorSquare.fill(chosenColor);

        ui.colorSelectBtn->setIcon(QIcon(colorSquare));
    }
}
