//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FBEGCYCLE_H_
#define PARSER_SCHEDULER_FIGURE_FBEGCYCLE_H_

#include "DoubleMeasureFigure.h"

class FBegCycle: public DoubleMeasureFigure
{
public:
    FBegCycle(Rect rect, std::string text, size_t page = 1)
        :
        DoubleMeasureFigure(rect, std::move(text), page)
    {}

    void acceptJsonFormer(JsonFormer &jFormer) override
    {
        jFormer.addToJson(*this);
    }
    std::string figureType() const override
    {
        return std::string("begin cycle");
    }
};


#endif //PARSER_SCHEDULER_FIGURE_FBEGCYCLE_H_
