//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_ONEMEASUREFIGURE_H_
#define PARSER_FIGURES_ONEMEASUREFIGURE_H_

#include "AbstractFigure.h"

struct Point{
  double x, y;
};

class OneMeasureFigure:AbstractFigure {
 public:
  OneMeasureFigure(Point begin, Point end, std::string sing);
  virtual std::string toJson() = 0 override;

 private:
  Point begin, end;
  std::string sign;
};

#endif //PARSER_FIGURES_ONEMEASUREFIGURE_H_
