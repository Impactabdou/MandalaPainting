#include "MainWindow.h"
#include <QPixmap>
#include <QColorDialog>
#include "view/linepreview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
    this->setMinimumSize(1000,1000);
    this->setMaximumSize(1000,1000);
    _canvas = new CanvasWidget(_ui->canvasFrame);

    _ui->canvasLayout->setContentsMargins(0, 0, 0, 0);
    _ui->canvasLayout->setSpacing(0);

    _ui->canvasLayout->addWidget(_canvas);

    // default color at start

    QPixmap colorSquare(16, 16);

    QColor chosenColor = Qt::black;

    colorSquare.fill(chosenColor);

    _ui->colorSelectBtn->setIcon(QIcon(colorSquare));

    connect(_ui->sliderSlices,
            &QSlider::valueChanged,
            _canvas,
            &CanvasWidget::setSlices);

    connect(_ui->sliderSlices,
            &QSlider::valueChanged,
            _ui->spinSlices,
            &QSpinBox::setValue);

    connect(_ui->spinSlices,
            QOverload<int>::of(&QSpinBox::valueChanged),
            _ui->sliderSlices,
            &QSlider::setValue);


    connect(_ui->comboCanvasSize,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            [this](const int index) {
                constexpr int sizes[] = {400, 600, 800};

                if (index >= 0 && index < 3)
                    _canvas->setCanvasSize(sizes[index], sizes[index]);
            });


    connect(_ui->sliderGrid,
            &QSlider::valueChanged,
            this,
            [this](const int value) {
                if (_ui->checkGrid->isChecked())
                    _canvas->setGridOpacity(value);
            });


    connect(_ui->checkGrid,
            &QCheckBox::toggled,
            this,
            [this](const bool checked) {
                _ui->sliderGrid->setEnabled(checked);

                checked ? _canvas->setGridOpacity(_ui->sliderGrid->value()) : _canvas->setGridOpacity(0);
            });

    connect(_ui->btnClear, &QPushButton::clicked, _canvas, &CanvasWidget::clear);

    connect(_ui->checkMirror, &QCheckBox::toggled, this, [this](const bool checked) {
        _canvas->setMirror(checked);
    });
    connect(_ui->sliderLineWidth, &QSlider::valueChanged, this, [this](const int value) {
        _canvas->setPenWidth(value);
        _ui->lineWidthPreview->setPenWidth(value);
    });

    connect(_ui->actionUndo, &QAction::triggered, this, &MainWindow::on_undo);
    connect(_ui->actionRedo, &QAction::triggered, this, &MainWindow::on_redo);


}


void MainWindow::on_undo() const {
    _canvas->undo();
    const int slices = _canvas->getSlices();
    _ui->sliderSlices->setValue(slices);
    _ui->spinSlices->setValue(slices);
}


void MainWindow::on_redo() const {
    _canvas->redo();
    int slices = _canvas->getSlices();
    _ui->sliderSlices->setValue(slices);
    _ui->spinSlices->setValue(slices);
}


void MainWindow::on_colorSelectBtn_clicked() {
    QColor chosenColor = QColorDialog::getColor(Qt::white, this, "Choose Color");

    if (chosenColor.isValid()) {
        QPixmap colorSquare(16, 16);
        colorSquare.fill(chosenColor);
        _ui->colorSelectBtn->setIcon(QIcon(colorSquare));


        _canvas->setPenColor(chosenColor);
        _ui->lineWidthPreview->setPenColor(chosenColor);
    }
}
