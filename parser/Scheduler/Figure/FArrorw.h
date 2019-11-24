//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FARRORW_H_
#define PARSER_SCHEDULER_FIGURE_FARRORW_H_

#include "SingleMeasureFigure.h"

class FArrow: public SingleMeasureFigure
{
public:
    FArrow(Point begin, Point end, std::string text)
        :
        SingleMeasureFigure(begin, end, std::move(text))
    {}
};

#endif //PARSER_SCHEDULER_FIGURE_FARRORW_H_
