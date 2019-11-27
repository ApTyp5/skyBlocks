//
// Created by arthur on 27.11.2019.
//

#ifndef META_H
#define META_H

#include <cstddef>

class Meta
{
public:
    size_t pageWidth() const
    { return 210; }
    size_t pageHeight() const
    { return 297; }
    size_t xMargin() const
    { return 20; }
    size_t yMargin() const
    { return 20; }
    size_t xPadding() const
    { return 20; }
    size_t yPadding() const
    { return 40; }
    size_t lineHeight() const
    { return 7; }
    size_t symbolWidth() const
    { return 3; }
    size_t blockSpace() const
    { return 5; }
};


#endif //META_H
