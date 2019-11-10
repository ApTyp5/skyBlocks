//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_PRIMITIVES_ABSTRACTPRIMITIVE_H_
#define PARSER_PRIMITIVES_ABSTRACTPRIMITIVE_H_

#include <string>
#include "../Figures/AbstractFigure.h"
#include "../Interfaces/Figurable.h"
struct Rect{
  double x_center, y_center;
  double width, height;
};

class AbstractPrimitive: Figurable {
 public:
  AbstractPrimitive(std::string text);

 private:
  std::string text;
};

#endif //PARSER_PRIMITIVES_ABSTRACTPRIMITIVE_H_
