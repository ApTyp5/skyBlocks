//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FLINE_H_
#define PARSER_SCHEDULER_FIGURE_FLINE_H_

#include "SingleMeasureFigure.h"

class FLine: public SingleMeasureFigure
{
public:
    FLine(Point begin, Point end, std::string text = "", size_t page = 1)
        :
        SingleMeasureFigure(begin, end, std::move(text), page)
    {}

    void acceptJsonFormer(JsonFormer &jFormer) override
    {
        jFormer.addToJson(*this);
    }
    std::string figureType() const override
    {
        return std::string("line");
    }
    AFigure *tryToConvertToFBegEnd() override
    {
        return this;
    }

    friend class FEmborderScheduler_pushForkLines_Test;
    friend class FEmborderScheduler_connectForkPartsLeftPageLess_Test;
};

#endif //PARSER_SCHEDULER_FIGURE_FLINE_H_
