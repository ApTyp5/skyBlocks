//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_AFIGURE_H_
#define PARSER_SCHEDULER_FIGURE_AFIGURE_H_

#include <string>
#include <ostream>
#include <boost/property_tree/ptree.hpp>
#include "../../JsonFormer/JsonFormer.h"


class AFigure: public JsonFormable
{
public:
    explicit AFigure(std::wstring text, size_t page = 1)
        : text(std::move(text)), page(page)
    {}

    virtual ~AFigure() = default;

    size_t getPage() const
    {
        return page;
    }

    const std::wstring &getText() const
    {
        return text;
    }

    virtual std::wstring figureType() const = 0;
    virtual AFigure *tryToConvertToFBegEnd() = 0;
    virtual bool isFFollow() const
    {
        return false;
    }
    virtual bool isSingleMeasureFigure() const
    {
        return false;
    }

private:
    size_t page;
    std::wstring text;
};

#endif //PARSER_SCHEDULER_FIGURE_AFIGURE_H_
