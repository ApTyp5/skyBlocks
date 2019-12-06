//
// Created by arthur on 05.12.2019.
//

#ifndef RECT_H
#define RECT_H

#include "Point.h"

struct sRect
{
    double w, h;
    sRect operator*=(double num)
    {
        w *= num;
        h *= num;
        return *this;
    }
};

struct Rect
{
    Point center;
    sRect size;
};

#endif //RECT_H
