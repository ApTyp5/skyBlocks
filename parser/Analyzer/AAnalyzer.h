//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_AANALYZER_H_
#define PARSER_ANALYZER_AANALYZER_H_

#include "../Errors/ParseError.h"
#include "../Tools/ptrVector.h"
#include "AccumulateErrors.h"
#include "Primitive/APrimitive.h"
#include "Primitive/ComplexPrimitive.h"

class AAnalyzer : public AccumulateErrors {
 public:
    explicit AAnalyzer(ptrVector<ParseError> &errors)
        : AccumulateErrors(errors)
    {}
    ~AAnalyzer() = default;
    virtual ComplexPrimitive *analyze(std::string text, size_t frontLine, size_t backLine) = 0;
};

#endif //PARSER_ANALYZER_AANALYZER_H_
