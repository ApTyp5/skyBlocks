//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PALGORITHM_H_
#define PARSER_PRIMITIVE_PALGORITHM_H_

#include "ComplexPrimitive.h"

class PAlgorithm: public ComplexPrimitive
{
public:
    explicit PAlgorithm(std::string text)
        :
        ComplexPrimitive(std::move(text))
    {}

    bool acceptScheduler(AScheduler &scheduler) const override
    {
        return scheduler.schedulePrimitive(*this, scheduler);
    }

    virtual std::string toString() override
    {
        std::string ans = "Algorithm\n" + ComplexPrimitive::toString();
        return ans;
    }
};

#endif //PARSER_PRIMITIVE_PALGORITHM_H_
