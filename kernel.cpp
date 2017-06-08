//Created by lyf

#include "kernel.h"
#include <QVector>
#include <QPoint>
#include <QDebug>

Kernel::Kernel(QObject *parent) : QObject(parent)
{
    cur_type = CIR;
    NF = new NetworkFlow;
}

Kernel::~Kernel()
{
    delete NF;
}

const QVector<QPoint>& Kernel::cirs()    //get()
{
    return _cirs;
}

const QVector<QPoint>& Kernel::tris()
{
    return _tris;
}

const QVector<QPoint>& Kernel::rects()
{
    return _rects;
}

vector<Line>& Kernel::lineList()
{
    return _lines;
}

//----------------------------------------------------

void Kernel::changeType(station st)    //被上级调用
{
    cur_type = st;
}

void Kernel::pointSlot(QPoint pos)     //调用add
{
    add(cur_type, pos);
    emit readyPaint();
}

void Kernel::add(station st, QPoint pos)
{
    switch (st) {
    case CIR:
        NF->addPoints(pos.x(), pos.y(), CIRCLE);
        _cirs.append(pos);
        break;
    case TRI:
        NF->addPoints(pos.x(), pos.y(), TRIANGLE);
        _tris.append(pos);
        break;
    case RECT:
        NF->addPoints(pos.x(), pos.y(), RECTANGLE);
        _rects.append(pos);
        break;
    default:
        break;
    }
}

void Kernel::reset()
{
    QVector<QPoint> temp0, temp1, temp2;
    //_cirs.swap(temp0);
    //_tris.swap(temp1);
    //_rects.swap(temp2);
    vector<Line> temp3;
    _lines.swap(temp3);
    NF->initMaxFlow();
    emit readyPaint();
}

//------------------------------------------------------

void Kernel::getMinCut() {
    qDebug() << "get_min called";
    NF->initMaxFlow();
    for (int i = 0; i < 100; i++)
        NF->onePersonCome();
    _lines =  NF->report();
}
