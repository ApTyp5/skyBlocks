//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PALGORITHM_H_
#define PARSER_PRIMITIVE_PALGORITHM_H_

#include "ComplexPrimitive.h"

class PAlgorithm: public ComplexPrimitive
{
public:
    explicit PAlgorithm(std::wstring text)
        :
        ComplexPrimitive(std::move(text))
    {}

    bool acceptScheduler(AScheduler &scheduler) const override
    {
        return scheduler.schedulePrimitive(*this);
    }

    std::wstring toString() override
    {
        std::wstring ans = L"Algorithm\n" + ComplexPrimitive::toString();
        return ans;
    }
};

#endif //PARSER_PRIMITIVE_PALGORITHM_H_
