//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_ACONSTRAINTOR_H_
#define PARSER_ANALYZER_ACONSTRAINTOR_H_

#include <string>

#include "AccumulateErrors.h"
#include "../Errors/ParseError.h"
#include "../../server/DataBaseConnection.h"

class AConstraintor: public AccumulateErrors
{
public:
    explicit AConstraintor(ptrVector<ParseError> &errors)
        : AccumulateErrors(errors)
    {}
    virtual bool findMain(size_t &first_index, size_t &last_index, const std::wstring &text) = 0;

    virtual std::wstring findFunc(
        size_t &line_num,
        std::wstring text,
        std::wstring name,
        DataBaseConnection &connection) = 0;

};

#endif //PARSER_ANALYZER_ACONSTRAINTOR_H_
