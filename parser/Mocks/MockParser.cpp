//
// Created by arthur on 22.11.2019.
//

#include "MockParser.h"

jsonString MockParser::parse(std::string text, Meta meta, AAnalyzeFactory *analyzeFactory, AScheduler *scheduler) {
  std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor());
  std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer());

  //std::string constrainted_text = constraintor->findMain(std::move(text));
  //ptrVector<APrimitive> primitives = analyzer->analyze(errors, constrainted_text);
  ptrVector<AFigure> figures = scheduler->schedule(ptrVector<APrimitive>());
  jsonString output = formJson(figures);

  return output;
}
