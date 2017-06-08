//
// Created by 乔逸凡 on 2017/3/31.
//

#include "NetworkFlow.h"
#include <cmath>
#include <memory.h>
#include <cstdio>
#include <QDebug>

bool equals(double a, double b) {
    if (abs(a - b) < eps)
        return 1;
    return 0;
}

NetworkFlow::NetworkFlow() {
    size = 2;
    pointList.push_back(Point(-1, -1));
    types.push_back(SUPERSOURCE);
    pointList.push_back(Point(-1, -1));
    types.push_back(SUPERSINK);
    flow = NULL;
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
    int SINK = 1;
    bool *vis = new bool [size];
    memset(vis, 0, sizeof(bool) * size);
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
    if (dist[SINK] < INF) return 1;
    return 0;
}

int NetworkFlow::DFS(int x, int a) {
    int SINK = 1;
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
    printf("GetMaxFlow\n");

    dist = new double [size];

    int source = rand() % size;
    while (types[source] != typeSource) {
        source = rand() % size;
    }
    int sink = rand() % size;
    while (types[sink] != typeSink) {
        sink = rand() % size;
    }
    flow[0][source] = 1;
    flow[sink][1] = 1;

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
    if (a == 0 || a == 1 || b == 0 || b == 1)
        return 0.1;
    return (pointList[a] - pointList[b]).len();
}

vector<Line> NetworkFlow::report() {
    qDebug() << "report called";
    vector<Line> ansList;
    for (int i = 2; i < size - 1; i++)
        for (int j = 2; j < size - 1; j++) {
            if (flow[i][j] < MAX_D) {
                qDebug("label: %d %d\n", i, j);
                ansList.push_back(Line(pointList[i], pointList[j], MAX_D - flow[i][j]));
            }
        }
    printf("AnsSize: %d %d\n", size, int(ansList.size()));
    return ansList;
}

void NetworkFlow::initMaxFlow() {
    if (flow != NULL) {
        for (int i = 0; i < size; i++)
            delete [] flow[i];
        delete [] flow;
    }
    flow = new int* [size];
    for (int i = 0; i < size; i++) {
        flow[i] = new int[size];
        for (int j = 0; j < size; j++)
            flow[i][j] = 0;
    }
    for (int i = 2; i < size - 1; i++)
        for (int j = 2; j < size - 1; j++)
            flow[i][j] = MAX_D;
}

void NetworkFlow::onePersonCome() {
    int type1 = rand() % 3 + 2;
    int type2 = rand() % 3 + 2;
    while (type2 == type1) {
        type2 = rand() % 3 + 2;
    }
    getMaxFlow(type1, type2);
}
