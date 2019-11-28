//
// Created by arthur on 27.11.2019.
//

#ifndef META_H
#define META_H

#include <cstddef>

class Meta
{
public:
    size_t pw() const
    { return 210; }
    size_t ph() const
    { return 297; }
    size_t xm() const
    { return 20; }
    size_t ym() const
    { return 20; }
    size_t xp() const
    { return 20; }
    size_t yp() const
    { return 40; }
    size_t lh() const
    { return 7; }
    size_t sw() const
    { return 3; }
    size_t bs() const
    { return 5; }
};


#endif //META_H