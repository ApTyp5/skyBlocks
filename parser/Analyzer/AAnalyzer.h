//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_AANALYZER_H_
#define PARSER_ANALYZER_AANALYZER_H_

#include "../ptrVector.h"
#include "Primitive/APrimitive.h"
#include "Primitive/ComplexPrimitive.h"
#include "../Error/Error.h"

class AAnalyzer {
 public:
  virtual ComplexPrimitive *analyze(ptrVector<Error> &errors, std::string text) = 0;
};
#endif //PARSER_ANALYZER_AANALYZER_H_
