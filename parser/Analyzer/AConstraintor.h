//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_ACONSTRAINTOR_H_
#define PARSER_ANALYZER_ACONSTRAINTOR_H_

#include <string>

#include "../Stubs/Stubs.h"
#include "AccumulateErrors.h"
#include "../Errors/ParseError.h"

class AConstraintor: public AccumulateErrors
{
public:
    explicit AConstraintor(ptrVector<ParseError> &errors)
        : AccumulateErrors(errors)
    {}
    virtual bool findMain(size_t &first_index, size_t &last_index, const std::string &text) = 0;

    virtual std::string findFunc(
        size_t &line_num,
        std::string text,
        std::string name,
        DataBaseConnection &connection) = 0;

};

#endif //PARSER_ANALYZER_ACONSTRAINTOR_H_
