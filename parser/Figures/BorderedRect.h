//
// Created by arthur on 12.11.2019.
//

#ifndef PARSER_FIGURES_BORDEREDRECT_H_
#define PARSER_FIGURES_BORDEREDRECT_H_

#include "DoubleMeasureFigure.h"

class BorderedRect: public DoubleMeasureFigure {
 public:
  BorderedRect(const Rect &rect, const std::string &text);
 public:
  std::string toJson() const override;
};

#endif //PARSER_FIGURES_BORDEREDRECT_H_
