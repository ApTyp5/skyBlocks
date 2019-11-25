//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PALGORITHM_H_
#define PARSER_PRIMITIVE_PALGORITHM_H_

#include "ComplexPrimitive.h"

class PAlgorithm: public ComplexPrimitive
{
public:
    PAlgorithm(std::string name, std::string text)
        :
        ComplexPrimitive(std::move(text)), name(std::move(name))
    {}

    bool acceptScheduler(AScheduler &scheduler) override
    {
        return scheduler.schedulePrimitive(*this, scheduler);
    }

    virtual std::string toString() override
    {
        std::string ans = "Algorithm\n" + ComplexPrimitive::toString();
        return ans;
    }

private:
    std::string name;
};

#endif //PARSER_PRIMITIVE_PALGORITHM_H_
