//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_ARROW_H_
#define PARSER_FIGURES_ARROW_H_

#include "OneMeasureFigure.h"

class Arrow: public OneMeasureFigure {
 public:
  Arrow(Point begin, Point end, std::string sign);
  std::string toJson() const override;
};

#endif //PARSER_FIGURES_ARROW_H_