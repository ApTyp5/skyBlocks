//
// Created by arthur on 22.11.2019.
//

#include "MockParser.h"

jsonString MockParser::parse(std::string text, AAnalyzeFactory *analyzeFactory, AScheduler *scheduler)
{
    ptrVector<Error> errors;
    std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor(errors));
    std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer(errors));
    ptrVector<AFigure> figures = scheduler->schedule(std::unique_ptr<ComplexPrimitive>());
    jsonString output = formJson(figures);

    return output;
}
