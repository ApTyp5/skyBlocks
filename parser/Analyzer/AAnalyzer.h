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
  virtual ComplexPrimitive *analyze(std::string text, size_t line_num) = 0;
 protected:

  void push_error(const std::string &message, int raw = -1, int col = -1) {
    errors.push_back(new Error(message, raw, col));
  }

  Error *pop_error() {
    return errors.pop_back();
  }

 private:
  ptrVector<Error> errors;
};
#endif //PARSER_ANALYZER_AANALYZER_H_
