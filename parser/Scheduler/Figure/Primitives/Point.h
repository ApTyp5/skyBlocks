//
// Created by arthur on 05.12.2019.
//

#ifndef POINT_H
#define POINT_H

#include <ostream>

struct Point
{
    size_t x, y;
    bool operator==(Point p) const
    {
        return (x == p.x && y == p.y);
    }
    std::ostream &operator<<(std::ostream &out)
    {
        out << "(" << x << ", " << y << ")";
        return out;
    }
};
#endif //POINT_H
