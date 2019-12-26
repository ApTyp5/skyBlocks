//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FARRORW_H_
#define PARSER_SCHEDULER_FIGURE_FARRORW_H_

#include "SingleMeasureFigure.h"

class FArrow: public SingleMeasureFigure
{
public:
    FArrow(Point begin, Point end, std::wstring text, size_t page = 1)
        :
        SingleMeasureFigure(begin, end, std::move(text), page)
    {}

    void acceptJsonFormer(JsonFormer &jFormer) override
    {
        return jFormer.addToJson(*this);
    }
    std::wstring figureType() const override
    {
        return std::wstring(L"arrow");
    }
    AFigure *tryToConvertToFBegEnd() override
    {
        return this;
    }
};

#endif //PARSER_SCHEDULER_FIGURE_FARRORW_H_
