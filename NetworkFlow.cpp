//
// Created by 乔逸凡 on 2017/3/31.
//

#include "NetworkFlow.h"

void NetworkFlow::addPoints(double x, double y, int type) {
    pointList.push_back(Point(x, y));
    types.push_back(type);
}

void NetworkFlow::addPoints(const Point& p, int type) {
    pointList.push_back(p);
    types.push_back(type);
}