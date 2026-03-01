#pragma once

#include <QMainWindow>
#include "ui_MandalaPaiting.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void on_colorSelectBtn_clicked();

private:
    Ui::MainWindow ui;
};
