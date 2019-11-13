//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_RECTANGLE_H_
#define PARSER_FIGURES_RECTANGLE_H_

#include "DoubleMeasureFigure.h"

class Rectangle: public DoubleMeasureFigure {
 public:
  Rectangle(Rect rect, std::string text);
  std::string toJson() const override;
};
std::string Rectangle::toJson() const {
  return std::__cxx11::string();
}

#endif //PARSER_FIGURES_RECTANGLE_H_
