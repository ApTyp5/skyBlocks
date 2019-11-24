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
  AConstraintor *createConstraintor(ptrVector<Error> &errors) override {
    return IndentConstraintor(errors);
  }
  AAnalyzer *createAnalyzer(ptrVector<Error> &errors) override {
    return new IndentAnalyzer(errors);
  }
};
#endif //PARSER_ANALYZER_INDENTANALYZEFACTORY_H_
