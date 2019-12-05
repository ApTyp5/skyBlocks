//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_AANALYZEFACTORY_H_
#define PARSER_ANALYZER_AANALYZEFACTORY_H_

#include <memory>

#include "AAnalyzer.h"
#include "AConstraintor.h"

class AAnalyzeFactory
{
public:
    virtual AConstraintor *createConstraintor(ptrVector<ParseError> &) = 0;
    virtual AAnalyzer *createAnalyzer(ptrVector<ParseError> &) = 0;
};

#endif //PARSER_ANALYZER_AANALYZEFACTORY_H_
