//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_
#define PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_

#include "../../ptrVector.h"
#include "APrimitive.h"

class ComplexPrimitive: public APrimitive
{
public:
    explicit ComplexPrimitive(std::string text)
        : APrimitive(std::move(text))
    {}

    virtual void addChild(APrimitive *child)
    {
        children.push_back(child);
    }

    virtual size_t childrenNum() const
    {
        return children.size();
    };

    const ptrVector<APrimitive> &getChildern() const
    {
        return children;
    };

    bool hasChildren() const override
    {
        return true;
    }

    virtual void startElseSection()
    {}

    virtual std::string toString()
    {
        std::string ans = "inner text:" + innerText + "\n"
                                                      "children:";
        for (size_t i = 0; i < childrenNum(); i++) {
            ans += "\t" + children[i]->toString();
        }
    }

protected:
    ptrVector<APrimitive> children;
};

#endif //PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_
