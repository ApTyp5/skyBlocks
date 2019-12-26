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
    explicit APrimitive(std::wstring text)
        : innerText(std::move(text))
    {}

    virtual ~APrimitive() = default;

    virtual bool acceptScheduler(AScheduler &scheduler) const = 0;

    virtual bool hasChildren() const
    {
        return false;
    }

    virtual std::wstring toString() const
    {
        return std::wstring(L"innerText:") + innerText + L"\n";
    }

protected:
    std::wstring innerText;

public:
    const std::wstring &getInnerText() const
    {
        return innerText;
    }
};
#endif //PARSER_PRIMITIVE_APRIMITIVE_H_
