//
// Created by 乔逸凡 on 2017/3/31.
//

#ifndef METRO_HELPER_NETWORKFLOW_H
#define METRO_HELPER_NETWORKFLOW_H

#include "Point.h"
#include <vector>

using namespace std;

class NetworkFlow {
    int size;
    vector<Point> pointList;
    vector<int> types;
public:
    void addPoints(double x, double y, int type);
    void addPoints(const Point& p, int type);
    double getMaxFlow();
};


#endif //METRO_HELPER_NETWORKFLOW_H
