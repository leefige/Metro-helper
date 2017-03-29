#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawpad.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>

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
    QHBoxLayout *mainLay;
    QVBoxLayout *rightLay;
    QSignalMapper *m;
};

#endif // MAINWINDOW_H
