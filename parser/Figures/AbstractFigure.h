//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_FIGURES_ABSTRACTFIGURE_H_
#define PARSER_FIGURES_ABSTRACTFIGURE_H_

#include <string>

class AbstractFigure {
 public:
  virtual std::string toJson() = 0;
};

#endif //PARSER_FIGURES_ABSTRACTFIGURE_H_
