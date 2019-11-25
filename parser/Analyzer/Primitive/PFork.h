//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PFORK_H_
#define PARSER_PRIMITIVE_PFORK_H_

#include "ComplexPrimitive.h"

class PFork: public ComplexPrimitive
{
public:
    explicit PFork(std::string text)
        : ComplexPrimitive(std::move(text)),
          is_else(false)
    {}

    bool acceptScheduler(AScheduler &scheduler) override
    {
        return scheduler.schedulePrimitive(*this, scheduler);
    }

    void addChild(APrimitive *child) override
    {
        if (is_else)
            elseChildren.push_back(child);
        else
            ComplexPrimitive::addChild(child);
    }

    void startElseSection() override
    {
        is_else = true;
    }

    std::string toString() override
    {
        std::string ans = "Fork\n" + ComplexPrimitive::toString();
        return ans;
    }

private:
    bool is_else;
    ptrVector<APrimitive> elseChildren;
};

#endif //PARSER_PRIMITIVE_PFORK_H_
