# Metro-helper
Help u get high mark in Mini-metro

> This is a Qt project  
  
## drawpad：一个继承qwidget重写的画板
### signals:
- mousePos: 发送鼠标左键单击位置
### slots:
- changeType(int): 改变绘制点的类型
  
  
## kernel：drawpad的内核，包括各类点的数据（vector类型）
### signals：
- readyPaint(): 对点的操作完毕后调用，告诉drawpad可以更新  
### slots:
- pointSlot(QPoint): 接受到鼠标点击位置，对点进行操作
