//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_
#define PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_

#include "../../Tools/ptrVector.h"
#include "APrimitive.h"

class ComplexPrimitive: public APrimitive
{
public:
    explicit ComplexPrimitive(std::wstring text)
        : APrimitive(std::move(text))
    {}

    virtual ~ComplexPrimitive() = default;

    virtual void addChild(APrimitive *child)
    {
        children.push_back(child);
    }

    virtual size_t childrenNum() const
    {
        return children.size();
    };

    const ptrVector<APrimitive> &getChildren() const
    {
        return children;
    };

    bool hasChildren() const override
    {
        return true;
    }

    virtual void startElseSection()
    {}

    virtual std::wstring toString()
    {
        std::wstring ans = L"inner text:" + innerText + L"\n"
                                                        L"children:";
        for (size_t i = 0; i < childrenNum(); i++) {
            ans += L"\t" + children[i]->toString();
        }
        return ans;
    }

protected:
    ptrVector<APrimitive> children;
};

#endif //PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_
