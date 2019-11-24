//
// Created by arthur on 09.11.2019.
//

#include "Parser.h"

jsonString Parser::parse(std::string text, Meta meta,
                         AAnalyzeFactory *analyzeFactory, AScheduler *scheduler)
{
    std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor(errors));
    std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer(errors));

    size_t line_num;
    std::string constrainted_text = constraintor->findMain(line_num, std::move(text));
    std::unique_ptr<ComplexPrimitive> algorithm(analyzer->analyze(constrainted_text, line_num));
    /*ptrVector<AFigure> figures = scheduler->schedule(algorithm, meta);
    jsonString output = formJson(figures);*/
    return algorithm->toString();
}

jsonString Parser::parseFunc(std::string text,
                             std::string name,
                             Meta meta,
                             AAnalyzeFactory *analyzeFactory,
                             AScheduler *scheduler)
{
    std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor(errors));
    std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer(errors));

    size_t line_num;
    std::string constrainted_text = constraintor->findFunc(line_num, std::move(text), std::move(name), connection);
    std::unique_ptr<ComplexPrimitive> algorithm(analyzer->analyze(constrainted_text, line_num));
    ptrVector<AFigure> figures = scheduler->schedule(algorithm, meta);
    jsonString output = formJson(figures);
    return output;
}

jsonString Parser::formJson(ptrVector<AFigure> &figures)
{
    return jsonString();
}
