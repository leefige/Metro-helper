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
    bool isShow;

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void resizeEvent(QResizeEvent *e);
    //void keyPressEvent(QKeyEvent *ek);

private:
    Kernel *ker;
    QImage* cir;
    QImage* tri;
    QImage* rect;

signals:
    void mouseClk(QPoint p);
    void mouseMov(QPoint p);

public slots:
    void changeType(int st);
    void cleanScreen();
    void planPath();
};

#endif // DRAWPAD_H
