#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_MandalaPainting.h"
#include "CanvasWidget.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void on_colorSelectBtn_clicked();
    void on_undo() const;
    void on_redo() const;
    void on_about() ;

private:
    Ui::MainWindow *_ui;
    CanvasWidget *_canvas;
};
#endif
