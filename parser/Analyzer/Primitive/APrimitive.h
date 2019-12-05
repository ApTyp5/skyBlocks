//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_APRIMITIVE_H_
#define PARSER_PRIMITIVE_APRIMITIVE_H_

#include <string>

#include "../../Scheduler/AScheduler.h"

class APrimitive
{
public:
    explicit APrimitive(std::string text)
        : innerText(std::move(text))
    {}

    virtual ~APrimitive() = default;

    virtual bool acceptScheduler(AScheduler &scheduler) const = 0;

    virtual bool hasChildren() const
    {
        return false;
    }

    virtual std::string toString() const
    {
        return std::string(
            "innerText:") + innerText + "\n";
    }

protected:
    std::string innerText;

public:
    const std::string &getInnerText() const
    {
        return innerText;
    }
};
#endif //PARSER_PRIMITIVE_APRIMITIVE_H_
