//
// Created by arthur on 05.12.2019.
//

#ifndef RECT_H
#define RECT_H

#include "Point.h"

struct sRect
{
    size_t w, h;
    sRect operator*=(size_t num)
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
