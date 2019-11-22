//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_DOUBLEMEASUREFIGURE_H_
#define PARSER_SCHEDULER_FIGURE_DOUBLEMEASUREFIGURE_H_

#include "AFigure.h"

class DoubleMeasureFigure : public AFigure {
 public:
  DoubleMeasureFigure(Point center, Rect rect, std::string text) :
      AFigure(std::move(text)), center(center), rect_(rect) {}
 private:
  Point center;
  Rect rect_;
};

#endif //PARSER_SCHEDULER_FIGURE_DOUBLEMEASUREFIGURE_H_
