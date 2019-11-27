//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FARRORW_H_
#define PARSER_SCHEDULER_FIGURE_FARRORW_H_

#include "SingleMeasureFigure.h"

class FArrow: public SingleMeasureFigure
{
public:
    FArrow(Point begin, Point end, std::string text, size_t page = 1)
        :
        SingleMeasureFigure(begin, end, std::move(text), page)
    {}
};

#endif //PARSER_SCHEDULER_FIGURE_FARRORW_H_
