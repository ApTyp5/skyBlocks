//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PCYCLE_H_
#define PARSER_PRIMITIVE_PCYCLE_H_

#include "ComplexPrimitive.h"

class PCycle: public ComplexPrimitive
{
public:
    PCycle(std::string beginCycleText, std::string endCycleText)
        :
        ComplexPrimitive(std::move(beginCycleText)),
        afterCycleText(std::move(endCycleText))
    {}

    bool acceptScheduler(AScheduler &scheduler) const override
    {
        return scheduler.schedulePrimitive(*this, scheduler);
    }

    std::string toString() override
    {
        std::string ans = "Cycle\n" + ComplexPrimitive::toString();
        return ans;
    }

    std::string getBeforeCycyleText() const
    {
        return getInnerText();
    }

    std::string getAfterCycleText() const
    {
        return afterCycleText;
    }

private:
    std::string afterCycleText;
};

#endif //PARSER_PRIMITIVE_PCYCLE_H_
