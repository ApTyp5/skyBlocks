//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_SINGLEMEASUREFIGURE_H_
#define PARSER_SCHEDULER_FIGURE_SINGLEMEASUREFIGURE_H_

#include <utility>

#include "AFigure.h"

class SingleMeasureFigure: public AFigure
{
public:
    SingleMeasureFigure(Point begin, Point end, std::string text)
        :
        AFigure(std::move(text)), begin(begin), end(end)
    {}

protected:
    Point begin, end;
};
#endif //PARSER_SCHEDULER_FIGURE_SINGLEMEASUREFIGURE_H_
