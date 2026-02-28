#pragma once

#include <QMainWindow>
#include "ui_MandalaPaiting.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    Ui::MandalaMainWindow ui;
};
