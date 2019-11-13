//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_LINE_H_
#define PARSER_FIGURES_LINE_H_

#include "OneMeasureFigure.h"

class Line: public OneMeasureFigure {
  Line(Point begin, Point end, std::string);
 public:
  std::string toJson() const override;
};

#endif //PARSER_FIGURES_LINE_H_
