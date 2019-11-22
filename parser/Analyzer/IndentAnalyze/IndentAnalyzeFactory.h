//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZEFACTORY_H_
#define PARSER_ANALYZER_INDENTANALYZEFACTORY_H_

#include "../AAnalyzeFactory.h"
#include "IndentAnalyzer.h"
#include "IndentConstraintor.h"

class IndentAnalyzeFactory : public AAnalyzeFactory {
 public:
  AConstraintor *createConstraintor() override {
    return new IndentConstraintor;
  }
  AAnalyzer *createAnalyzer() override {
    return new IndentAnalyzer;
  }
};
#endif //PARSER_ANALYZER_INDENTANALYZEFACTORY_H_
