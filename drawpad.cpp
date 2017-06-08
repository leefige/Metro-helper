#include "drawpad.h"
#include "kernel.h"

#include <QPen>
#include <QColor>
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
    ker = new Kernel(this);
    cir = new QImage(":/img/cir_pic");      //图标
    tri = new QImage(":/img/tri_pic");
    rect = new QImage(":/img/rect_pic");

    setAutoFillBackground(true);
    QPixmap pixmap(":/img/bg");
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    setMouseTracking(true);
    //setPalette(QPalette(Qt::white));
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
    return;
}

void DrawPad::resizeEvent(QResizeEvent *e)
{
    QPixmap pixmap(":/img/bg");
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap.scaled(this->size())));
    this->setPalette(palette);
    return;
}

void DrawPad::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    //Draw lines here in future
    if(isShow)
    {
        vector<Line> lines = ker->lineList();
        int lsize = lines.size();
        qDebug() << "line_size is " << lsize;
        for(int i = 0; i < lsize; i++)
        {
            if(lsize == 0)
            {
                qDebug() << "line_size is 0\n";
                break;
            }
            qDebug("(%.2f, %.2f), (%.2f, %.2f), %d\n",
                   lines[i].first.xx(), lines[i].first.yy(),
                   lines[i].second.xx(), lines[i].second.yy(),
                   lines[i].d);
            QColor color(255, 255, 0);  //yellow
            color.setAlpha(int(255 * lines[i].d / MAX_D * lines[i].d / MAX_D * lines[i].d / MAX_D));  //alpha is decided by d
            QPen pen(color);
            pen.setWidth(15);
            p.setPen(pen);
            p.drawLine(int(lines[i].first.xx()), int(lines[i].first.yy()),
                       int(lines[i].second.xx()), int(lines[i].second.yy()));
            qDebug() << "end for\n";
        }
    }

    //Draw stations
    foreach(QPoint c, ker->cirs())
    {
        QRect r(c.x()-10, c.y()-10, 20, 20);   //20*20图标
        p.drawImage(r, *cir);
    }

    foreach(QPoint c, ker->tris())
    {
        QRect r(c.x()-10, c.y()-10, 20, 20);   //20*20图标
        p.drawImage(r, *tri);
    }

    foreach(QPoint c, ker->rects())
    {
        QRect r(c.x()-10, c.y()-10, 20, 20);   //20*20图标
        p.drawImage(r, *rect);
    }
    qDebug() << "end paint\n";
    return;
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
    //int x = pos.x(), y = pos.y();
    //qDebug()<<x<<y;
    emit mouseMov(pos);
}

void DrawPad::cleanScreen()
{
    ker->reset();
    update();
}

void DrawPad::planPath()
{
    ker->getMinCut();
    update();
}

void DrawPad::mc()
{
    ker->getMinCut();
}

void DrawPad::initMc()
{
    ker->NF->initMaxFlow();
}

void DrawPad::stopMc()
{
    ker->stop_and_report();
}
