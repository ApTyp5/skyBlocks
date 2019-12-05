//
// Created by arthur on 09.11.2019.
//

#include "Parser.h"

jsonString Parser::parse(std::string text, AAnalyzeFactory *analyzeFactory, AScheduler *scheduler)
{
    std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor(errors));
    std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer(errors));
    jsonString output;
    JsonFormer former;

    size_t front_line, back_line;
    if (constraintor->findMain(front_line, back_line, text)) {
        std::unique_ptr<ComplexPrimitive> algorithm(analyzer->analyze(text, front_line, 0));
        ptrVector<AFigure> figures = scheduler->schedule(algorithm);
        output += former.formJson(figures);
    }

    output += former.formJson(errors);

    return output;
}

jsonString Parser::parseFunc(std::string text, std::string name, AAnalyzeFactory *analyzeFactory, AScheduler *scheduler)
{
    std::unique_ptr<AConstraintor> constraintor(analyzeFactory->createConstraintor(errors));
    std::unique_ptr<AAnalyzer> analyzer(analyzeFactory->createAnalyzer(errors));

    size_t line_num;
    std::string constrainted_text = constraintor->findFunc(line_num, std::move(text), std::move(name), connection);
    std::unique_ptr<ComplexPrimitive> algorithm(analyzer->analyze(constrainted_text, line_num, 0));
    ptrVector<AFigure> figures = scheduler->schedule(algorithm);
    JsonFormer former;
    jsonString output = former.formJson(figures);
    return output;
}
