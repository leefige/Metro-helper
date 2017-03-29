#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pad = new DrawPad(this);
    mainLay = new QHBoxLayout(this);
    rightLay = new QVBoxLayout(this);

    ui->central->setLayout(mainLay);
    rightLay->addWidget(ui->typeBox);
    rightLay->addStretch();
    mainLay->addWidget(pad);
    mainLay->addLayout(rightLay);

    //map：转换信号类型
    m = new QSignalMapper(this);
    connect(ui->cirBtn, SIGNAL(clicked(bool)), m, SLOT(map()));
    connect(ui->triBtn, SIGNAL(clicked(bool)), m, SLOT(map()));
    connect(ui->rectBtn, SIGNAL(clicked(bool)), m, SLOT(map()));

    m->setMapping(ui->cirBtn, Kernel::CIR);
    m->setMapping(ui->triBtn, Kernel::TRI);
    m->setMapping(ui->rectBtn, Kernel::RECT);

    connect(m, SIGNAL(mapped(int)), pad, SLOT(changeType(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
