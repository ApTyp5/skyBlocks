//
// Created by arthur on 05.12.2019.
//

#ifndef POINT_H
#define POINT_H

#include <ostream>
#include <cmath>

struct Point
{
    double x, y;
    static constexpr double eps = 1e-3;
    bool operator==(Point p) const
    {
        return (fabs(x - p.x) < eps && fabs(y - p.y) < eps);
    }
    std::ostream &operator<<(std::ostream &out)
    {
        out << "(" << x << ", " << y << ")";
        return out;
    }
};
#endif //POINT_H
