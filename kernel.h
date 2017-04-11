#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include "NetworkFlow.h"

class Kernel : public QObject
{
    Q_OBJECT

public:
    enum station{TRI = 3, CIR = 0, RECT = 4};

    station cur_type;

    void add(station st, QPoint pos); //暂时只有加

public:
    explicit Kernel(QObject *parent = 0);

    const QVector<QPoint>& cirs();    //get()
    const QVector<QPoint>& tris();
    const QVector<QPoint>& rects();
    const vector<pair<Point, Point>>& lineList();

    void changeType(station st);
    void reset();
    NetworkFlow NF;

private:
    QVector<QPoint> _cirs;          //三种点
    QVector<QPoint> _tris;
    QVector<QPoint> _rects;

signals:
    void readyPaint();

public slots:
    void pointSlot(QPoint pos);     //调用add
};

#endif // KERNEL_H
