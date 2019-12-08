//
// Created by arthur on 24.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_ALPHABET_PYTHONLIKEALPHABET_H_
#define PARSER_ANALYZER_INDENTANALYZE_ALPHABET_PYTHONLIKEALPHABET_H_

#include "BaseIndentAlphabet.h"

class PythonLikeAlphabet: public BaseIndentAlphabet
{
public:
    PythonLikeAlphabet()
        :
        BaseIndentAlphabet(
            "if",
            "else",
            "while",
            "call",
            "def",
            {' ', '\t'},
            {';'}
        )
    {}
};

#endif //PARSER_ANALYZER_INDENTANALYZE_ALPHABET_PYTHONLIKEALPHABET_H_
