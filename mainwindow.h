#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawpad.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DrawPad *pad;
    QLabel *posLab;
    QHBoxLayout *mainLay;
    QVBoxLayout *rightLay;
    QSignalMapper *m;

public slots:
    void showMousePos(QPoint pos);
};

#endif // MAINWINDOW_H
