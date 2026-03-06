#pragma once

#include "ui_MandalaPainting.h"
#include "CanvasWidget.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void on_colorSelectBtn_clicked();

private:
    Ui::MainWindow *_ui;
    CanvasWidget *_canvas;
};
