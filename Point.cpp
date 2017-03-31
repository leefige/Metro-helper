//
// Created by 乔逸凡 on 2017/3/31.
//

#include "Point.h"
#include <cmath>

Point Point::operator - (const Point &b) {
    Point c;
    c.x = x - b.x;
    c.y = y - b.y;
    return c;
}

Point Point::operator + (const Point &b) {
    Point c;
    c.x = x + b.x;
    c.y = y + b.y;
    return c;
}

double Point::len() {
    return sqrt(x * x + y * y);
}

double dist(Point a, Point b) {
    return (a - b).len();
}

Point::Point(double x, double y) : x(x), y(y) {}

bool Point::operator == (const Point &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Point::operator != (const Point &rhs) const {
    return !(rhs == *this);
}


