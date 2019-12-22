//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FBEGEND_H_
#define PARSER_SCHEDULER_FIGURE_FBEGEND_H_

#include "FFollow.h"

class FBegEnd: public FFollow
{
public:
    FBegEnd(Rect rect, std::string text, size_t page = 1)
        :
        FFollow(rect, std::move(text), page)
    {}
    FBegEnd(FFollow &follow)
        :
        FFollow(follow)
    {}

    void acceptJsonFormer(JsonFormer &jFormer) override
    {
        jFormer.addToJson(*this);
    }
    std::string figureType() const override
    {
        return std::string("begin end");
    }
    AFigure *tryToConvertToFBegEnd() override
    {
        return this;
    }
};

#endif //PARSER_SCHEDULER_FIGURE_FBEGEND_H_
