//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_HROMBUS_H_
#define PARSER_FIGURES_HROMBUS_H_

#include "DoubleMeasureFigure.h"
class Hrombus: public DoubleMeasureFigure {
 public:
  Hrombus(Rect rect, std::string text);
  std::string toJson() const override;
};

#endif //PARSER_FIGURES_HROMBUS_H_
