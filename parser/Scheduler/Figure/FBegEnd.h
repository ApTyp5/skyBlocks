//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FBEGEND_H_
#define PARSER_SCHEDULER_FIGURE_FBEGEND_H_

#include "DoubleMeasureFigure.h"

class FBegEnd : public DoubleMeasureFigure {
 public:
  FBegEnd(Point center, Rect rect, std::string text) :
      DoubleMeasureFigure(center, rect, std::move(text)) {}
};

#endif //PARSER_SCHEDULER_FIGURE_FBEGEND_H_
