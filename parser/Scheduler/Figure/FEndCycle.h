//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_FENDCYCLE_H_
#define PARSER_SCHEDULER_FIGURE_FENDCYCLE_H_

#include "DoubleMeasureFigure.h"

class FEndCycle : public DoubleMeasureFigure {
  FEndCycle(Point point, Rect rect, std::string text) :
      DoubleMeasureFigure(point, rect, std::move(text)) {}
};

#endif //PARSER_SCHEDULER_FIGURE_FENDCYCLE_H_
