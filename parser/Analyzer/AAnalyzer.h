//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_AANALYZER_H_
#define PARSER_ANALYZER_AANALYZER_H_

#include "../Errors/Error.h"
#include "../Tools/ptrVector.h"
#include "AccumulateErrors.h"
#include "Primitive/APrimitive.h"
#include "Primitive/ComplexPrimitive.h"

class AAnalyzer : public AccumulateErrors {
 public:
  explicit AAnalyzer(ptrVector<Error> &errors) : AccumulateErrors(errors) {}
    ~AAnalyzer() = default;
    virtual ComplexPrimitive *analyze(std::string text, size_t line_num) = 0;
};

#endif //PARSER_ANALYZER_AANALYZER_H_
