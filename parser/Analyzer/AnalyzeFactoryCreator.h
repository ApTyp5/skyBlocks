//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_ANALYZEFACTORYCREATOR_H_
#define PARSER_ANALYZER_ANALYZEFACTORYCREATOR_H_

#include "AAnalyzeFactory.h"
#include "AnalyzeFactoryType.h"
#include "IndentAnalyze/IndentAnalyzeFactory.h"

class AnalyzeFactoryCreator
{
public:
    static AAnalyzeFactory *create(AnalyzeFactoryType type = Indent, AlphabetType aType = PythonLike)
    {
        switch (type) {
            default:
            case Indent: return new IndentAnalyzeFactory(aType);
        }
    }
};

#endif //PARSER_ANALYZER_ANALYZEFACTORYCREATOR_H_
