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
        _cirs.append(pos);
        break;
    case TRI:
        _tris.append(pos);
        break;
    case RECT:
        _rects.append(pos);
        break;
    default:
        break;
    }
}
