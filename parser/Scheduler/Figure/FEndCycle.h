//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FENDCYCLE_H_
#define PARSER_SCHEDULER_FIGURE_FENDCYCLE_H_

#include "DoubleMeasureFigure.h"

class FEndCycle: public DoubleMeasureFigure
{
public:
    FEndCycle(Rect rect, std::string text, size_t page = 1)
        :
        DoubleMeasureFigure(rect, std::move(text), page)
    {}

    void acceptJsonFormer(JsonFormer &jFormer) override
    {
        jFormer.addToJson(*this);
    }
    std::string figureType() const override
    {
        return std::string("end cycle");
    }
};

#endif //PARSER_SCHEDULER_FIGURE_FENDCYCLE_H_
