//
// Created by arthur on 24.11.2019.
//

#ifndef PARSER_ANALYZER_ACCUMULATEERRORS_H_
#define PARSER_ANALYZER_ACCUMULATEERRORS_H_

#include "../Tools/ptrVector.h"
#include "../Errors/ParseError.h"

class AccumulateErrors
{
public:
    explicit AccumulateErrors(ptrVector<ParseError> &errors)
        : errors(errors)
    {}

protected:
    void push_error(const std::string &message, int raw = -1, int col = -1)
    {
        errors.push_back(new ParseError(message, raw, col));
    }

private:
    ptrVector<ParseError> &errors;

    friend class FIndentPythonLikeConstraintor_findMainNoMain_Test;
};

#endif //PARSER_ANALYZER_ACCUMULATEERRORS_H_
