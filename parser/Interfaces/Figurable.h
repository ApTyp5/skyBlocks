//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_INTERFACES_FIGURABLE_H_
#define PARSER_INTERFACES_FIGURABLE_H_

#include "../Figures/AbstractFigure.h"
class Figurable{
  virtual AbstractFigure *toFigure() const = 0;
};

#endif //PARSER_INTERFACES_FIGURABLE_H_
