//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZEFACTORY_H_
#define PARSER_ANALYZER_INDENTANALYZEFACTORY_H_

#include "../AAnalyzeFactory.h"
#include "IndentAnalyzer.h"
#include "IndentConstraintor.h"
#include "Alphabet/RuPseudoCodeAlphabet.h"
#include "../AlphabetType.h"
#include "Alphabet/IndentAlphabetCreator.h"

class IndentAnalyzeFactory: public AAnalyzeFactory
{
public:
    IndentAnalyzeFactory(AlphabetType aType)
        : AAnalyzeFactory(aType)
    {};
    AConstraintor *createConstraintor(ptrVector<ParseError> &errors) override
    {
        return new IndentConstraintor(errors, IndentAlphabetCreator::create(getAType()));
    }
    AAnalyzer *createAnalyzer(ptrVector<ParseError> &errors) override
    {
        return new IndentAnalyzer(errors, IndentAlphabetCreator::create(getAType()));
    }
};

#endif //PARSER_ANALYZER_INDENTANALYZEFACTORY_H_
