//
// Created by 乔逸凡 on 2017/3/31.
//

#ifndef METRO_HELPER_NETWORKFLOW_H
#define METRO_HELPER_NETWORKFLOW_H

#include "Point.h"
#include "Line.h"
#include <vector>
#include <queue>
#include <cmath>

#define SUPERSOURCE 0
#define SUPERSINK 1
#define RECTANGLE 2
#define CIRCLE 3
#define TRIANGLE 4
#define INF 100000000
#define eps 1e-15
#define MAX_D 12

using namespace std;

class NetworkFlow {
    int size;
    vector<Point> pointList;
    vector<int> types;
    int DFS(int x,int a);
    bool SPFA();
    double* dist;
    int** flow;
    double distance(int a, int b);

public:
    NetworkFlow();
    void addPoints(double x, double y, int type);
    void addPoints(const Point& p, int type);
    int getMaxFlow(int typeSource, int typeSink);
    void initMaxFlow();
    vector<Line> report();
    virtual ~NetworkFlow();
};

bool equals(double a, double b);

#endif //METRO_HELPER_NETWORKFLOW_H
