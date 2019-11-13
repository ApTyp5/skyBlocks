//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_INTERFACES_FIGURABLE_H_
#define PARSER_INTERFACES_FIGURABLE_H_

#include "../Figures/DoubleMeasureFigure.h"

// Double Measure Figurable
class DMFigurable{
 public:
  virtual DoubleMeasureFigure *toFigure(const Rect &rect) const = 0;
};

#endif //PARSER_INTERFACES_FIGURABLE_H_
