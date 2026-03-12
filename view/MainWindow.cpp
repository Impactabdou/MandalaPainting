#include "MainWindow.h"
#include <QPixmap>
#include <QColorDialog>
#include "view/linepreview.h"
#include <QDebug>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
    _ui->canvasFrame->setStyleSheet(
        "QFrame {"
        "background-image: url(://frame.png);"
        "background-position: center;"
        "background-repeat: no-repeat;"
        "}"
    );
    this->setMinimumSize(1000, 1000);
    this->setMaximumSize(1000, 1000);
    _canvas = new CanvasWidget(_ui->canvasFrame);

    _ui->canvasLayout->setContentsMargins(0, 0, 0, 0);
    _ui->canvasLayout->setSpacing(0);

    _ui->canvasLayout->addWidget(_canvas);

    this->setStyleSheet(

        "QMainWindow {"
        "background-color: #0f1a14;"
        "}"

        "QWidget {"
        "background-color: #0f1a14;"
        "color: #e7efe9;"
        "font-family: 'Segoe UI';"
        "font-size: 13px;"
        "}"

        "#canvasFrame {"
        "background: transparent;"
        "}"

        "QFrame {"
        "background-color: #16251d;"
        "border-radius: 12px;"
        "border: 1px solid #243a2f;"
        "}"

        "QPushButton {"
        "background-color: #2e7d57;"
        "color: #eaf7ef;"
        "border: none;"
        "border-radius: 8px;"
        "padding: 6px 14px;"
        "}"

        "QPushButton:hover {"
        "background-color: #359c6b;"
        "}"

        "QPushButton:pressed {"
        "background-color: #256947;"
        "}"

        "QSlider::groove:horizontal {"
        "background: #243a2f;"
        "height: 6px;"
        "border-radius: 3px;"
        "}"

        "QSlider::handle:horizontal {"
        "background: #3fa374;"
        "width: 16px;"
        "border-radius: 8px;"
        "margin: -5px 0;"
        "}"

        "QSpinBox, QComboBox {"
        "background: #1c2f25;"
        "border: 1px solid #2c4a3c;"
        "border-radius: 6px;"
        "padding: 4px;"
        "color: #e7efe9;"
        "}"

        "QCheckBox::indicator {"
        "width: 14px;"
        "height: 14px;"
        "}"

        "QCheckBox::indicator:checked {"
        "background-color: #3fa374;"
        "border-radius: 3px;"
        "}"

        "QMenuBar {"
        "background-color: #0f1a14;"
        "border-bottom: 1px solid #243a2f;"
        "}"

        "QMenuBar::item:selected {"
        "background: #1c2f25;"
        "}"

        "QMenu {"
        "background-color: #16251d;"
        "border: 1px solid #243a2f;"
        "}"

        "QMenu::item:selected {"
        "background-color: #2e7d57;"
        "}"

    );

    // default color at start

    QPixmap colorSquare(16, 16);

    const QColor chosenColor = Qt::black;

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
    connect(_ui->actionAbout, &QAction::triggered, this, &MainWindow::on_about);
    connect(_ui->actionSave_As, &QAction::triggered, this, [this]() {
        _canvas->saveToFile(QDir::homePath());
    });
    connect(_ui->actionQuit, &QAction::triggered, this, [this]() {
        close();
    });
    connect(_ui->btnPalette, &QPushButton::toggled, this, [this]() {
        _canvas->set_colorful();
    });
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
    QColor chosenColor = QColorDialog::getColor(Qt::white, this, tr("Choose Color"));

    if (chosenColor.isValid()) {
        QPixmap colorSquare(16, 16);
        colorSquare.fill(chosenColor);
        _ui->colorSelectBtn->setIcon(QIcon(colorSquare));


        _canvas->setPenColor(chosenColor);
        _ui->lineWidthPreview->setPenColor(chosenColor);
    }
}

void MainWindow::on_about() {
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("About Ensi-Mandala"));

    msgBox.setText(tr(
        "Ensi-Mandala: An interactive tool for drawing Mandalas.<br><br> Abderrahmene KABAR - Mohamed ABDESSALAME <br><br> (C) 2026 "));

    QPixmap logo("://ENSICAEN.png");
    msgBox.setIconPixmap(logo.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    msgBox.setStandardButtons(QMessageBox::Ok);

    msgBox.exec();
}
