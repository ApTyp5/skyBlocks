//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_DOUBLEMEASUREFIGURE_H_
#define PARSER_FIGURES_DOUBLEMEASUREFIGURE_H_

#include "AbstractFigure.h"
#include "OneMeasureFigure.h"

struct Rect{
  double cx, cy;
  double len, width;
};

class DoubleMeasureFigure: public AbstractFigure {
 public:
  DoubleMeasureFigure(Rect rect, std::string text);

 private:
  Rect rect;
  std::string text;
};

#endif //PARSER_FIGURES_DOUBLEMEASUREFIGURE_H_
