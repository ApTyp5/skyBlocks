//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_ACONSTRAINTOR_H_
#define PARSER_ANALYZER_ACONSTRAINTOR_H_

#include <string>

#include "../Stubs/Stubs.h"
#include "AccumulateErrors.h"

class AConstraintor: public AccumulateErrors
{
public:
    explicit AConstraintor(ptrVector<Error> &errors)
        : AccumulateErrors(errors)
    {}
    virtual std::string findMain(std::string text) = 0;
    virtual std::string findFunc(std::string text,
                                 std::string name, DataBaseConnection &connection) = 0;
};

#endif //PARSER_ANALYZER_ACONSTRAINTOR_H_
