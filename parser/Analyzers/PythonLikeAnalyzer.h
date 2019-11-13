//
// Created by arthur on 12.11.2019.
//

#ifndef PARSER_ANALYZERS_PYTHONLIKEANALYZER_H_
#define PARSER_ANALYZERS_PYTHONLIKEANALYZER_H_

#include "AbstractAnalyzer.h"

class PythonLikeAnalyzer: public AbstractAnalyzer {
 public:
  std::vector<AbstractPrimitive *> analyze(std::string text) override;
};

#endif //PARSER_ANALYZERS_PYTHONLIKEANALYZER_H_
