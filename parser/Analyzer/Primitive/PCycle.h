//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PCYCLE_H_
#define PARSER_PRIMITIVE_PCYCLE_H_

#include "ComplexPrimitive.h"

class PCycle: public ComplexPrimitive
{
public:
    PCycle(std::wstring beginCycleText, std::wstring endCycleText)
        :
        ComplexPrimitive(std::move(beginCycleText)),
        afterCycleText(std::move(endCycleText))
    {}

    bool acceptScheduler(AScheduler &scheduler) const override
    {
        return scheduler.schedulePrimitive(*this);
    }

    std::wstring toString() override
    {
        std::wstring ans = L"Cycle\n" + ComplexPrimitive::toString();
        return ans;
    }

    std::wstring getBeforeCycyleText() const
    {
        return getInnerText();
    }

    std::wstring getAfterCycleText() const
    {
        return afterCycleText;
    }

private:
    std::wstring afterCycleText;
};

#endif //PARSER_PRIMITIVE_PCYCLE_H_
