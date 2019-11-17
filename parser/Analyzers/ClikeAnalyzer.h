//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_ANALYZERS_CLIKEANALYZER_H_
#define PARSER_ANALYZERS_CLIKEANALYZER_H_

#include "AnalyzerType.h"
#include "BaseAnalyzer.h"

class ClikeAnalyzer : public BaseAnalyzer {
 public:
 protected:
  void ifHandler(std::string line) override;
  void whileHandler(std::string line) override;
  void followHandler(std::string line) override;
};

#endif //PARSER_ANALYZERS_CLIKEANALYZER_H_
