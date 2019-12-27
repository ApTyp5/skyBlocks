//
// Created by arthur on 09.11.2019.
//

#include "Parser.h"
#include "Analyzer/Primitive/PAlgorithm.h"

jsonString Parser::parse(std::string text, AAnalyzeFactory *analyzeFactory, AScheduler *scheduler)
{
    std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor(errors));
    std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer(errors));
    JsonFormer former;

    size_t front_line, back_line;
    if (constraintor->findMain(front_line, back_line, text)) {
      std::unique_ptr<PAlgorithm> algorithm(analyzer->analyze(text, front_line, back_line));
      ptrVector<AFigure> figures = scheduler->schedule(algorithm);
        former.addFigures(figures);
    }

  former.addErrors(errors);
  errors.clear();

    return former.getJson();
}

jsonString Parser::parseFunc(std::string text, std::string name, AAnalyzeFactory *analyzeFactory, AScheduler *scheduler)
{
    std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor(errors));
    std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer(errors));
    JsonFormer former;

    size_t front_line, back_line;
    if (constraintor->findMain(front_line, back_line, text)) {
      std::unique_ptr<PAlgorithm> algorithm(analyzer->analyze(text, front_line, back_line));
      ptrVector<AFigure> figures = scheduler->schedule(algorithm);
        former.addFigures(figures);
    }

    former.addErrors(errors);

    return former.getJson();
}
