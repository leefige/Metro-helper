#include "drawpad.h"
#include "kernel.h"

#include <QPen>
#include <QImage>
#include <QPoint>
#include <QPainter>
#include <QPalette>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>

DrawPad::DrawPad(QWidget *parent) : QWidget(parent)
{
    ker = new Kernel(this);
    cir = new QImage(":/img/cir_pic");      //图标
    tri = new QImage(":/img/tri_pic");
    rect = new QImage(":/img/rect_pic");

    setMouseTracking(true);
    setPalette(QPalette(Qt::white));
    setAutoFillBackground(true);
    //setMinimumSize(800,600);

    connect(this, SIGNAL(mouseClk(QPoint)), ker, SLOT(pointSlot(QPoint)));
    connect(ker, SIGNAL(readyPaint()), this, SLOT(update()));
}

DrawPad::~DrawPad()
{
    delete cir;
    delete tri;
    delete rect;
}

void DrawPad::changeType(int st)
{
    ker->changeType(Kernel::station(st));
}

void DrawPad::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    foreach(QPoint c, ker->cirs())
    {
        QRect r(c.x()-7.5, c.y()-7.5, 15, 15);   //15*15图标
        p.drawImage(r, *cir);
    }

    foreach(QPoint c, ker->tris())
    {
        QRect r(c.x()-7.5, c.y()-7.5, 15, 15);   //15*15图标
        p.drawImage(r, *tri);
    }

    foreach(QPoint c, ker->rects())
    {
        QRect r(c.x()-7.5, c.y()-7.5, 15, 15);   //15*15图标
        p.drawImage(r, *rect);
    }

    //Draw lines here in future
}

void DrawPad::mousePressEvent(QMouseEvent *ev)     //发送位置
{
    QPoint pos = ev->pos();
    int x = pos.x(), y = pos.y();
    qDebug()<<x<<y;
    emit mouseClk(pos);
}

void DrawPad::mouseMoveEvent(QMouseEvent *ev)
{
    QPoint pos = ev->pos();
    int x = pos.x(), y = pos.y();
    qDebug()<<x<<y;
    emit mouseMov(pos);
}

vector<pair<Point, Point>> DrawPad::getMinCut() {
    ker->NF.getMaxFlow(CIRCLE, TRIANGLE);
    return ker->NF.report();
}
