#include "drawpad.h"
#include "kernel.h"

#include <QPen>
#include <QBrush>
#include <QImage>
#include <QPoint>
#include <QPainter>
#include <QPalette>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>
#include <vector>

DrawPad::DrawPad(QWidget *parent) : QWidget(parent)
{
    isShow = 0;
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

    //Draw lines here in future
    if(isShow)
    {
        int lsize = ker->lines.size();
        qDebug() << lsize;
        for(int i = 0; i < lsize; i++)
        {
            qDebug("%.2f %.2f %.2f %.2f\n", ker->lines[i].first.xx(), ker->lines[i].first.yy(),
                   ker->lines[i].second.xx(), ker->lines[i].second.yy());
            QPen pen(Qt::cyan);
            pen.setWidth(10);
            p.setPen(pen);
            p.drawLine(int(ker->lines[i].first.xx()), int(ker->lines[i].first.yy()),
                       int(ker->lines[i].second.xx()), int(ker->lines[i].second.yy()));
        }
    }
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
    //qDebug()<<x<<y;
    emit mouseMov(pos);
}

void DrawPad::cleanScreen() {
    ker->reset();
}

vector<pair<Point, Point>> DrawPad::getMinCut() {
    qDebug() << "get_min called";
    ker->NF.initMaxFlow();
    ker->NF.getMaxFlow(CIRCLE, TRIANGLE);
    ker->NF.getMaxFlow(CIRCLE, RECTANGLE);
    ker->NF.getMaxFlow(TRIANGLE, RECTANGLE);
    return ker->NF.report();
}

void DrawPad::change_isShow()
{
    qDebug() << "is_show changed";
    isShow = 1;
    ker->lines = getMinCut();
    update();
}
