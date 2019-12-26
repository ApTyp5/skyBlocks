//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PFUNC_H_
#define PARSER_PRIMITIVE_PFUNC_H_

#include "APrimitive.h"

class PFunc: public APrimitive
{
public:
    PFunc(std::wstring name, std::wstring text)
        :
        APrimitive(std::move(text)), name(std::move(name))
    {}

    bool acceptScheduler(AScheduler &scheduler) const override
    {
        return scheduler.schedulePrimitive(*this);
    }

    virtual std::wstring toString() const
    {
        return std::wstring(L"Func(") + name + std::wstring(L")\n") +
            APrimitive::toString();
    }

    const std::wstring &getName() const
    {
        return name;
    }

protected:
    std::wstring name;
};
#endif //PARSER_PRIMITIVE_PFUNC_H_
