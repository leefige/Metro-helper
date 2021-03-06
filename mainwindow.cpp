#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QString>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    opacity = 0.70;
    ui->setupUi(this);

    setAutoFillBackground(true);

    setMouseTracking(true);
    setMinimumSize(800, 600);
    setWindowOpacity(opacity);
    ui->statusBar->setStyleSheet("QStatusBar::item{border: 0px}");

    posLab = new QLabel(this);
    pad = new DrawPad(this);
    mainLay = new QHBoxLayout(this);
    rightLay = new QVBoxLayout(this);
    bottomLay = new QHBoxLayout(this);

    ui->statusBar->addWidget(posLab);
    ui->central->setLayout(mainLay);
    rightLay->addWidget(ui->typeBox);
    rightLay->addWidget(ui->setBox);
    rightLay->addWidget(ui->showBtn);
    bottomLay->addWidget(ui->startBt);
    bottomLay->addWidget(ui->stopBt);
    rightLay->addLayout(bottomLay);

    rightLay->addStretch();
    mainLay->addWidget(pad, 10);
    mainLay->addLayout(rightLay, 1);

    timer = new QTimer(this);
    timer->setInterval(10);

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
    connect(ui->showBtn, SIGNAL(clicked(bool)), this, SLOT(showPath()));
    connect(timer, SIGNAL(timeout()), pad, SLOT(mc()));
    connect(ui->startBt, SIGNAL(clicked(bool)), timer, SLOT(start()));
    connect(ui->startBt, SIGNAL(clicked(bool)), pad, SLOT(initMc()));
    connect(ui->stopBt, SIGNAL(clicked(bool)), timer, SLOT(stop()));
    connect(ui->stopBt, SIGNAL(clicked(bool)), pad, SLOT(stopMc()));
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

void MainWindow::showPath()
{
    bool flag = ui->showBtn->isChecked();
    qDebug() << "flag is: " << flag;
    ui->showBtn->setChecked(flag);
    pad->isShow = flag;
    qDebug() << "is_show changed: " << pad->isShow;
    if(pad->isShow)
    {
        pad->planPath();
    }
    else
    {
        pad->cleanScreen();
    }
    return;
}

void MainWindow::setOpacity(int opa)
{
    opacity = (float)opa / 100;
    setWindowOpacity(opacity);
}
