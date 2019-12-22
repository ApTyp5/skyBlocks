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
    SingleMeasureFigure(Point begin, Point end, std::string text, size_t page)
        :
        AFigure(std::move(text), page), begin(begin), end(end)
    {}

    Point getBegin() const
    {
        return begin;
    }
    Point getEnd() const
    {
        return end;
    }
    bool isSingleMeasureFigure() const
    {
        return true;
    }

protected:
    Point begin, end;

    friend class FEmborderScheduler_pushForkLines_Test;
    friend class FEmborderScheduler_connectForkPartsRightPageLess_Test;
};
#endif //PARSER_SCHEDULER_FIGURE_SINGLEMEASUREFIGURE_H_
