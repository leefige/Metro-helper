//
// Created by 乔逸凡 on 2017/3/31.
//

#ifndef METRO_HELPER_POINT_H
#define METRO_HELPER_POINT_H


class Point {
    double x, y;
public:
    Point() = default;

    Point(double x, double y);

    bool operator == (const Point &rhs) const;

    bool operator != (const Point &rhs) const;

    Point operator - (const Point &b);

    Point operator + (const Point &b);

    double len();

    friend double dist(Point a, Point b);
};

double dist(Point a, Point b);

#endif //METRO_HELPER_POINT_H
