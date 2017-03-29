#ifndef DRAWPAD_H
#define DRAWPAD_H

#include <QWidget>
#include "kernel.h"

class DrawPad : public QWidget
{
    Q_OBJECT
public:
    explicit DrawPad(QWidget *parent = 0);
    ~DrawPad();

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    //void keyPressEvent(QKeyEvent *ek);

private:
    Kernel *ker;

    QImage* cir;
    QImage* tri;
    QImage* rect;

signals:
    void mousePos(QPoint p);

public slots:
    void changeType(int st);
};

#endif // DRAWPAD_H