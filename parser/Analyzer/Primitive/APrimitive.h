//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_APRIMITIVE_H_
#define PARSER_PRIMITIVE_APRIMITIVE_H_

#include <string>

class APrimitive
{
public:
    explicit APrimitive(std::string text)
        : innerText(std::move(text))
    {}

    virtual bool hasChildren() const
    {
        return false;
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
