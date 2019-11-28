//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTCONSTRAINTOR_H_
#define PARSER_ANALYZER_INDENTCONSTRAINTOR_H_

#include "../../Error/Error.h"
#include "../../Tools/ptrVector.h"
#include "../AConstraintor.h"

class IndentConstraintor: public AConstraintor
{
public:
    explicit IndentConstraintor(ptrVector<Error> &errors)
        : AConstraintor(errors)
    {}
    std::string findFunc(size_t &line_num, std::string text, std::string name, DataBaseConnection &connection) override;
    std::string findMain(size_t &line_num, std::string text) override;
};

#endif //PARSER_ANALYZER_INDENTCONSTRAINTOR_H_
