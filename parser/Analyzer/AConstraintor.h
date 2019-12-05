//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_ACONSTRAINTOR_H_
#define PARSER_ANALYZER_ACONSTRAINTOR_H_

#include <string>

#include "../Stubs/Stubs.h"
#include "AccumulateErrors.h"
#include "../Errors/Error.h"

class AConstraintor: public AccumulateErrors
{
public:
    explicit AConstraintor(ptrVector<Error> &errors)
        : AccumulateErrors(errors)
    {}
    virtual std::string findMain(size_t &line_num, std::string text)
    { return ""; };

    virtual std::string findFunc(
        size_t &line_num,
        std::string text,
        std::string name,
        DataBaseConnection &connection)
    { return ""; };
};

#endif //PARSER_ANALYZER_ACONSTRAINTOR_H_
