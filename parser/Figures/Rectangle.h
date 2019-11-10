//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_RECTANGLE_H_
#define PARSER_FIGURES_RECTANGLE_H_

#include "DoubleMeasureFigure.h"

class Rectangle: public DoubleMeasureFigure {
 public:
  Rectangle(Rect rect, std::string text);
  std::string toJson() override;
};

#endif //PARSER_FIGURES_RECTANGLE_H_
