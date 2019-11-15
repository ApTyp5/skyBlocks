//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_ANALYZERS_ABSTRACTANALYZER_H_
#define PARSER_ANALYZERS_ABSTRACTANALYZER_H_

#include <vector>
#include <memory>

#include "AnalyzerType.h"
#include "../Primitives/AbstractPrimitive.h"

typedef std::vector<std::shared_ptr<AbstractPrimitive>> Primitives;

class AbstractAnalyzer {
 public:
  virtual Primitives analyze(std::string text) = 0;
};

#endif //PARSER_ANALYZERS_ABSTRACTANALYZER_H_
