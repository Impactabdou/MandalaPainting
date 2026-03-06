#include "MainWindow.h"
#include <QPixmap>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    canvas = new CanvasWidget(ui->canvasFrame);

    ui->canvasLayout->setContentsMargins(0, 0, 0, 0);
    ui->canvasLayout->setSpacing(0);

    ui->canvasLayout->addWidget(canvas);

    // default color at start

    QPixmap colorSquare(16, 16);

    QColor chosenColor = Qt::black;

    colorSquare.fill(chosenColor);

    ui->colorSelectBtn->setIcon(QIcon(colorSquare));

    connect(ui->sliderSlices,
            &QSlider::valueChanged,
            canvas,
            &CanvasWidget::setSlices);

    connect(ui->sliderSlices,
            &QSlider::valueChanged,
            ui->spinSlices,
            &QSpinBox::setValue);

    connect(ui->spinSlices,
            QOverload<int>::of(&QSpinBox::valueChanged),
            ui->sliderSlices,
            &QSlider::setValue);


    connect(ui->comboCanvasSize,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            [this](const int index) {
                constexpr int sizes[] = {400, 600, 800};

                if (index >= 0 && index < 3)
                    canvas->setCanvasSize(sizes[index], sizes[index]);
            });


    connect(ui->sliderGrid,
            &QSlider::valueChanged,
            this,
            [this](const int value) {
                if (ui->checkGrid->isChecked())
                    canvas->setGridOpacity(value);
            });


    connect(ui->checkGrid,
            &QCheckBox::toggled,
            this,
            [this](const bool checked) {
                ui->sliderGrid->setEnabled(checked);

                checked ? canvas->setGridOpacity(ui->sliderGrid->value()) : canvas->setGridOpacity(0);
            });
}


void MainWindow::on_colorSelectBtn_clicked() {
    QColor chosenColor = QColorDialog::getColor(Qt::white, this, "Choose Color");

    if (chosenColor.isValid()) {
        QPixmap colorSquare(16, 16);

        colorSquare.fill(chosenColor);

        ui->colorSelectBtn->setIcon(QIcon(colorSquare));
    }
}
