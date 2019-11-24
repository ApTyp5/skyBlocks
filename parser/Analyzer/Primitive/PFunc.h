//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PFUNC_H_
#define PARSER_PRIMITIVE_PFUNC_H_

#include "APrimitive.h"

class PFunc: public APrimitive
{
public:
    PFunc(std::string name, std::string text)
        :
        APrimitive(std::move(text)), name(std::move(name))
    {}

    virtual std::string toString() const
    {
        return std::string("Func(") + name + std::string(")\n") +
            APrimitive::toString();
    }

protected:
    std::string name;
};
#endif //PARSER_PRIMITIVE_PFUNC_H_
