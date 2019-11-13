//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_PRIMITIVES_SUBSCHEME_H_
#define PARSER_PRIMITIVES_SUBSCHEME_H_

#include "AbstractPrimitive.h"

class SubScheme: public AbstractPrimitive {
 public:
  SubScheme(std::string text, std::string name, size_t innerBlocks);
  DoubleMeasureFigure *toFigure(const Rect &rect) const override;
 private:
  std::string name;
  size_t innerBlocks;
};

#endif //PARSER_PRIMITIVES_SUBSCHEME_H_
