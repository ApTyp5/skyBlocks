//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_BEGEND_H_
#define PARSER_FIGURES_BEGEND_H_

#include "DoubleMeasureFigure.h"

class BegEnd {
 public:
  BegEnd(Rect rect, std::string text);
  std::string toJson() override;
};

#endif //PARSER_FIGURES_BEGEND_H_
