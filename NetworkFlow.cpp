//
// Created by 乔逸凡 on 2017/3/31.
//

#include "NetworkFlow.h"
#include <cmath>
#include <memory.h>
#include <cstdio>

bool equals(double a, double b) {
    if (abs(a - b) < eps)
        return 1;
    return 0;
}

NetworkFlow::NetworkFlow() {
    size = 1;
    pointList.push_back(Point(-1, -1));
    types.push_back(SUPERSOURCE);
}

void NetworkFlow::addPoints(double x, double y, int type) {
    pointList.push_back(Point(x, y));
    types.push_back(type);
    size++;
}

void NetworkFlow::addPoints(const Point& p, int type) {
    pointList.push_back(p);
    types.push_back(type);
    size++;
}

bool NetworkFlow::SPFA() {
    bool *vis = new bool [size];
    memset(vis, 0, sizeof(vis) * size);
    for (int i = 0; i < size; i++) {
        dist[i] = INF;
    }
    queue<int> Q;
    Q.push(0);
    dist[0] = 0;
    vis[0] = 1;
    while (!Q.empty()) {
        int x = Q.front();
        vis[x] = 0;
        Q.pop();
        for (int i = 0; i < size; i++)
            if (x != i && flow[x][i] != 0) {
                if (dist[i] > distance(x, i) + dist[x]) {
                    dist[i] = distance(x, i) + dist[x];
                    if (!vis[i]) Q.push(i), vis[i] = 1;
                }
            }
    }
    delete [] vis;
    if (dist[size - 1] < INF) return 1;
    return 0;
}

int NetworkFlow::DFS(int x, int a) {
    int SINK = size - 1;
    if (x == SINK || a == 0) return a;
    int cur = 0, f;
    for (int i = 0; i < size; i++) {
        if (x != i && flow[x][i] > 0) {
            if (equals(dist[i], dist[x] + distance(x, i))) {
                f = DFS(i, min(a, flow[x][i]));
                if (f <= 0) continue;
                flow[x][i] -= f;
                flow[i][x] += f;
                cur += f;
                a -= f;
                if (a == 0) break;
            }
        }
    }
    return cur;
}

int NetworkFlow::getMaxFlow(int typeSource, int typeSink) {
    printf("GetHere\n");

    for (int i = 1; i < size - 1; i++)
        for (int j = 1; j < size - 1; j++)
            flow[i][j] = 6;
    dist = new double [size];
    int SINK = size - 1;
    for (int i = 0; i < size; i++) {
        if (types[i] == typeSource) {
            flow[i][0] = 6;
            flow[0][i] = 6;
        }
        if (types[i] == typeSink) {
            flow[i][SINK] = 6;
            flow[SINK][i] = 6;
        }
    }
    int flow = 0;
    while (SPFA()) {
        flow += DFS(0, INF);
    }
    delete [] dist;
    return flow;
}

NetworkFlow::~NetworkFlow() {
    for (int i = 0; i < size; i++)
        delete [] flow[i];
    delete [] flow;
}

double NetworkFlow::distance(int a, int b) {
    if (a == 0 || a == size - 1 || b == 0 || b == size - 1)
        return 0.1;
    return (pointList[a] - pointList[b]).len();
}

vector<pair<Point, Point>> NetworkFlow::report() {
    vector<pair<Point, Point>> ansList;
    for (int i = 1; i < size - 1; i++)
        for (int j = 1; j < size - 1; j++) {
            if (flow[i][j] == 0) {
                printf("label: %d %d\n", i, j);
                pair<Point, Point> ans(pointList[i], pointList[j]);
                ansList.push_back(ans);
            }
        }
    return ansList;
}

void NetworkFlow::initMaxFlow() {
    addPoints(-1, -1, SUPERSINK);
    flow = new int* [size];
    for (int i = 0; i < size; i++) {
        flow[i] = new int[size];
        for (int j = 0; j < size; j++)
            flow[i][j] = 0;
    }
}
