//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_AANALYZEFACTORY_H_
#define PARSER_ANALYZER_AANALYZEFACTORY_H_

#include <memory>

#include "AAnalyzer.h"
#include "AConstraintor.h"
#include "AlphabetType.h"

class AAnalyzeFactory
{
public:
    AAnalyzeFactory(AlphabetType aType = PythonLike)
        : aType(aType)
    {}
    virtual AConstraintor *createConstraintor(ptrVector<ParseError> &) = 0;
    virtual AAnalyzer *createAnalyzer(ptrVector<ParseError> &) = 0;
protected:
    AlphabetType getAType()
    { return aType; }
private:
    AlphabetType aType;
};

#endif //PARSER_ANALYZER_AANALYZEFACTORY_H_
