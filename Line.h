
//Created by lyf @ 2017.5.23

#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line
{
public:
    Line() = default;
    Line(const Point& _first, const Point& _second, const int& _d);

    Point first;
    Point second;
    int d;
};

#endif // LINE_H
