//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_PRIMITIVES_CYCLE_H_
#define PARSER_PRIMITIVES_CYCLE_H_

#include "AbstractPrimitive.h"

class Cycle: public AbstractPrimitive {
 public:
  Cycle(std::string topText, std::string bottomText, size_t innerNum);
  DoubleMeasureFigure *toFigure(const Rect &rect) const override;

 private:
  std::string bottomText;
  size_t innnerNum;
};

#endif //PARSER_PRIMITIVES_CYCLE_H_
