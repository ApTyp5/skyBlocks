//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FLINE_H_
#define PARSER_SCHEDULER_FIGURE_FLINE_H_

#include "SingleMeasureFigure.h"

class FLine : public SingleMeasureFigure {
 public:
  FLine(Point begin, Point end, std::string text) :
      SingleMeasureFigure(begin, end, std::move(text)) {}
};

#endif //PARSER_SCHEDULER_FIGURE_FLINE_H_