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

> 另外还有我的一点想法：
- 现在点的数据完整地保存在kernel里，我想NF是不是也可以直接从kernel里获取点的数据这样就不用重复拷贝？而且一致性也比较好。。。
- 我的想法是，可以给NF一个类似parent的指针，构造的时候就指向kernel，然后需要点的数据就直接访问kernel的对应接口，而且点的类型在kernel里也有一个enum类型的定义，可以把那个定义移到MF里。
乔神可以在下一版里考虑一下，不过话说你要是想访问kernel里的数据的话，可能需要qt的lib。。。这样是不是就不能用clion了[捂脸]