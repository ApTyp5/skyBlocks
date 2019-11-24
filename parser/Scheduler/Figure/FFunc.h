//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FFUNC_H_
#define PARSER_SCHEDULER_FIGURE_FFUNC_H_

#include "DoubleMeasureFigure.h"

class FFunc: public DoubleMeasureFigure
{
public:
    FFunc(Point center, Rect rect, std::string text)
        :
        DoubleMeasureFigure(center, rect, std::move(text))
    {}
};

#endif //PARSER_SCHEDULER_FIGURE_FFUNC_H_
