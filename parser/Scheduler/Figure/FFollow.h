//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FFOLLOW_H_
#define PARSER_SCHEDULER_FIGURE_FFOLLOW_H_

#include "DoubleMeasureFigure.h"

class FFollow: public DoubleMeasureFigure
{
public:
    FFollow(Rect rect, std::string text, size_t page = 1)
        :
        DoubleMeasureFigure(rect, std::move(text), page)
    {}

    void acceptJsonFormer(JsonFormer &jFormer) override
    {
        jFormer.addToJson(*this);
    }
    std::string figureType() const override
    {
        return std::string("follow");
    }
    AFigure *tryToConvertToFBegEnd() override
    {
        return this;
    }
    bool isFFollow() const override
    {
        return true;
    }
    static bool onOneLine(AFigure *fig1, AFigure *fig2)
    {
        if (!fig1->isFFollow()) return false;
        if (!fig2->isFFollow()) return false;
        auto *follow1 = dynamic_cast<FFollow *>(fig1);
        auto *follow2 = dynamic_cast<FFollow *>(fig2);

        return follow1->getCenter().x == follow2->getCenter().x;
    }
};

#endif //PARSER_SCHEDULER_FIGURE_FFOLLOW_H_
