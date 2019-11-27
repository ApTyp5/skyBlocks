//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FFOLLOW_H_
#define PARSER_SCHEDULER_FIGURE_FFOLLOW_H_

#include "DoubleMeasureFigure.h"

class FFollow: public DoubleMeasureFigure
{
public:
    FFollow(Rect rect, std::string text, size_t page = 1)
        :
        DoubleMeasureFigure(rect, std::move(text), page)
    {}
};

#endif //PARSER_SCHEDULER_FIGURE_FFOLLOW_H_
