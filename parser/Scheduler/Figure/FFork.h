//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FFORK_H_
#define PARSER_SCHEDULER_FIGURE_FFORK_H_

#include "DoubleMeasureFigure.h"

class FFork: public DoubleMeasureFigure
{
public:
    FFork(Rect rect, std::string text, size_t page = 1)
        :
        DoubleMeasureFigure(rect, std::move(text), page)
    {}

    jsonString acceptJsonFormer(boost::property_tree::ptree &tree, JsonFormer &jFormer) override
    {
        return jFormer.addToTree(tree, *this);
    }
};

#endif //PARSER_SCHEDULER_FIGURE_FFORK_H_
