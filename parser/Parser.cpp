//
// Created by arthur on 09.11.2019.
//

#include "Parser.h"

#include <utility>

jsonString Parser::parse(std::string text, Meta meta,
                         AAnalyzeFactory *analyzeFactory, AScheduler *scheduler) {
  std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor(errors));
  std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer(errors));

  std::string constrainted_text = constraintor->findMain(std::move(text));
  ptrVector<APrimitive> primitives = analyzer->analyze(constrainted_text);
  ptrVector<AFigure> figures = scheduler->schedule(primitives);
  jsonString output = formJson(figures);
  return output;
}

jsonString Parser::parseFunc(std::string text,
                             std::string name,
                             Meta meta,
                             AAnalyzeFactory *analyzeFactory,
                             AScheduler *scheduler) {
  std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor());
  std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer());

  std::string constrainted_text = constraintor->findFunc(std::move(text), std::move(name), connection);
  ptrVector<APrimitive> primitives = analyzer->analyze(errors, constrainted_text);
  ptrVector<AFigure> figures = scheduler->schedule(primitives);
  jsonString output = formJson(figures);
  return output;
}
