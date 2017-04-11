# Metro-helper
Help u get high mark in Mini-metro

> This is a Qt project  
  
## drawpad：一个继承qwidget重写的画板
### signals:
- mouseClk(): 发送鼠标单击位置
- mouseMov(): 鼠标移动时发射鼠标位置
### slots:
- changeType(int): 改变绘制点的类型
  
  
## kernel：drawpad的内核，包括各类点的数据
### signals：
- readyPaint(): 对点的操作完毕后调用，告诉drawpad可以更新  
### slots:
- pointSlot(QPoint): 接受到鼠标点击位置，对点进行操作

### surfaces：
- vector<pair<Point, Point>>& lineList() : 面向上层的drawpad，用于获取需要绘制的边列表，现在drawpad唯一的功能就是绘图。
- void getMinCut() : 可以被drawpad调用，其功能是调用NF计算边，结果是更新kernel的私有成员_lines，而上层的drawpad可以通过调用lineList()获取这个列表

## NetworkFlow：包含于kernel，kernel的私有成员，所有运算接口只与kernel交互

