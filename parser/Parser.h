//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER__PARSER_H_
#define PARSER__PARSER_H_

#include <string>
#include <vector>

#include "AnalyzerType.h"
#include "SchedulerType.h"

#include "Analyzers/AbstractAnalyzer.h"
#include "Schedulers/AbstractScheduler.h"

#include "Figures/AbstractFigure.h"
#include "Primitives/AbstractPrimitive.h"

class Parser {
 public:
  std::string parse(std::string, AnalyzerType = CLike, SchedulerType = Gost);

 private:
  std::string figuresToString(std::vector<AbstractFigure *> figures);
};

#endif //PARSER__PARSER_H_
