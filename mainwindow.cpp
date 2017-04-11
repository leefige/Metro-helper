#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    opacity = 0.70;
    ui->setupUi(this);
    setMouseTracking(true);
    setMinimumSize(400, 300);
    setWindowOpacity(opacity);
    ui->statusBar->setStyleSheet("QStatusBar::item{border: 0px}");

    posLab = new QLabel(this);
    pad = new DrawPad(this);
    mainLay = new QHBoxLayout(this);
    rightLay = new QVBoxLayout(this);

    ui->statusBar->addWidget(posLab);
    ui->central->setLayout(mainLay);
    rightLay->addWidget(ui->typeBox);
    rightLay->addWidget(ui->setBox);
    rightLay->addWidget(ui->showBtn);
    rightLay->addStretch();
    mainLay->addWidget(pad, 4);
    mainLay->addLayout(rightLay, 1);

    //map：转换信号类型
    m = new QSignalMapper(this);
    connect(ui->cirBtn, SIGNAL(clicked(bool)), m, SLOT(map()));
    connect(ui->triBtn, SIGNAL(clicked(bool)), m, SLOT(map()));
    connect(ui->rectBtn, SIGNAL(clicked(bool)), m, SLOT(map()));

    m->setMapping(ui->cirBtn, Kernel::CIR);
    m->setMapping(ui->triBtn, Kernel::TRI);
    m->setMapping(ui->rectBtn, Kernel::RECT);

    connect(m, SIGNAL(mapped(int)), pad, SLOT(changeType(int)));
    connect(ui->opaSlider,SIGNAL(valueChanged(int)),this, SLOT(setOpacity(int)));
    connect(pad, SIGNAL(mouseMov(QPoint)), this, SLOT(showMousePos(QPoint)));
    connect(ui->actionCS, SIGNAL(triggered(bool)), pad, SLOT(cleanScreen()));
    connect(ui->showBtn, SIGNAL(clicked(bool)), pad, SLOT(change_isShow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMousePos(QPoint pos)
{
    //qDebug()<<"showpos";
    int x = pos.x();
    int y = pos.y();
    QString text = QString("x: ") + QString::number(x) + QString(", y: ") + QString::number(y);
    posLab->setText(text);
}

void MainWindow::setOpacity(int opa)
{
    opacity = (float)opa / 100;
    setWindowOpacity(opacity);
}
