//
// Created by arthur on 27.11.2019.
//

#ifndef FCONTINUE_H
#define FCONTINUE_H

#include <utility>

#include "DoubleMeasureFigure.h"

class FContinue: public DoubleMeasureFigure
{
public:
    FContinue(Rect rect, size_t page = 1)
        :
        DoubleMeasureFigure(rect, std::string(name), page)
    {
        if (counter % 2) {
            counter = 0;
            ++*name;
        }
        else {
            counter++;
        }
    }

private:
    static char name[2];
    static size_t counter;
};

#endif //FCONTINUE_H
