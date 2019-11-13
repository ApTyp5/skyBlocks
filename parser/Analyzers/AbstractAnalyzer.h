//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_ANALYZERS_ABSTRACTANALYZER_H_
#define PARSER_ANALYZERS_ABSTRACTANALYZER_H_

#include <vector>

#include "../AnalyzerType.h"
#include "../Primitives/AbstractPrimitive.h"

class AbstractAnalyzer {
 public:
  virtual std::vector<AbstractPrimitive *> analyze(std::string text) = 0;
};

#endif //PARSER_ANALYZERS_ABSTRACTANALYZER_H_
