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
    explicit AFigure(std::string text, size_t page = 1)
        : text(std::move(text)), page(page)
    {}

    virtual ~AFigure() = default;

    size_t getPage() const
    { return page; }

    const std::string &getText() const
    {
        return text;
    }

    virtual std::string figureType() const = 0;

private:
    size_t page;
    std::string text;
};

#endif //PARSER_SCHEDULER_FIGURE_AFIGURE_H_
