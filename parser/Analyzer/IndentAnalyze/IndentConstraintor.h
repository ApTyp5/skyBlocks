//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTCONSTRAINTOR_H_
#define PARSER_ANALYZER_INDENTCONSTRAINTOR_H_

#include "../../Errors/ParseError.h"
#include "../../Tools/ptrVector.h"
#include "../AConstraintor.h"
#include "Tools/IndentAnalyzerUtils.h"
#include "Alphabet/BaseIndentAlphabet.h"

class IndentConstraintor: public AConstraintor
{
public:
    explicit IndentConstraintor(ptrVector<ParseError> &errors, BaseIndentAlphabet *alphabet)
        : AConstraintor(errors), AlphaBet(alphabet)
    {}

    std::string findFunc(size_t &line_num, std::string text, std::string name,
                         DataBaseConnection &connection) override;

    bool findMain(size_t &first_index, size_t &back_index, const std::string &text) override;

private:
    std::unique_ptr<BaseIndentAlphabet> AlphaBet;
};

#endif //PARSER_ANALYZER_INDENTCONSTRAINTOR_H_
