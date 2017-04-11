#include "kernel.h"
#include <QVector>
#include <QPoint>
#include <QDebug>

Kernel::Kernel(QObject *parent) : QObject(parent)
{
    cur_type = CIR;
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
        NF.addPoints(pos.x(), pos.y(), CIRCLE);
        _cirs.append(pos);
        break;
    case TRI:
        NF.addPoints(pos.x(), pos.y(), TRIANGLE);
        _tris.append(pos);
        break;
    case RECT:
        NF.addPoints(pos.x(), pos.y(), RECTANGLE);
        _rects.append(pos);
        break;
    default:
        break;
    }
}

void Kernel::reset()
{
    QVector<QPoint> temp0, temp1, temp2;
    _cirs.swap(temp0);
    _tris.swap(temp1);
    _rects.swap(temp2);
    emit readyPaint();
}
