//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZER_H_
#define PARSER_ANALYZER_INDENTANALYZER_H_

#include "../AAnalyzer.h"

class IndentAnalyzer : public AAnalyzer {
 public:
  ptrVector<APrimitive> analyze(ptrVector<Error> &errors, std::string text) override;
};

#endif //PARSER_ANALYZER_INDENTANALYZER_H_
