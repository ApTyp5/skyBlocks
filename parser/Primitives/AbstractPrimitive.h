//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_PRIMITIVES_ABSTRACTPRIMITIVE_H_
#define PARSER_PRIMITIVES_ABSTRACTPRIMITIVE_H_

#include <string>
#include <bits/unique_ptr.h>
#include "../Figures/AbstractFigure.h"
#include "../Interfaces/Figurable.h"


class AbstractPrimitive: public DMFigurable {
 public:
  explicit AbstractPrimitive(std::string text) : text(text) {}

 private:
  std::string text;
};

#endif //PARSER_PRIMITIVES_ABSTRACTPRIMITIVE_H_
