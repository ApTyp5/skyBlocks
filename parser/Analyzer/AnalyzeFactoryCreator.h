//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_ANALYZEFACTORYCREATOR_H_
#define PARSER_ANALYZER_ANALYZEFACTORYCREATOR_H_

#include "AnalyzeFactoryType.h"
#include "AAnalyzeFactory.h"
#include "IndentAnalyze/IndentAnalyzeFactory.h"

class AnalyzeFactoryCreator {
 public:
  static AAnalyzeFactory *create(AnalyzeFactoryType type) {
    switch (type) {
      default:
      case AnalyzeFactoryType::Indent: return new IndentAnalyzeFactory;
    }
  }
};

#endif //PARSER_ANALYZER_ANALYZEFACTORYCREATOR_H_
