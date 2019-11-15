//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_ANALYZERS_CLIKEANALYZER_H_
#define PARSER_ANALYZERS_CLIKEANALYZER_H_

#include "AnalyzerType.h"
#include "AbstractAnalyzer.h"

class ClikeAnalyzer: public AbstractAnalyzer {
 public:
  Primitives analyze(std::string text) override;
};

#endif //PARSER_ANALYZERS_CLIKEANALYZER_H_
