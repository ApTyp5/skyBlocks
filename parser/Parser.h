//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER__PARSER_H_
#define PARSER__PARSER_H_

#include <memory>
#include <string>
#include <vector>

#include "Analyzer/AAnalyzeFactory.h"
#include "Errors/ParseError.h"
#include "JsonFormer/JsonFormer.h"
#include "Scheduler/AScheduler.h"
#include "Tools/ptrVector.h"


class Parser
{
public:
    explicit Parser(DataBaseConnection connection = DataBaseConnection())
    {}

    virtual jsonString parse(std::wstring text,
                             AAnalyzeFactory *analyzeFactory,
                             AScheduler *scheduler);

    virtual jsonString parseFunc(std::wstring text,
                                 std::wstring name,
                                 AAnalyzeFactory *analyzeFactory,
                                 AScheduler *scheduler);

private:
    DataBaseConnection connection;
    ptrVector<ParseError> errors;

    friend class parser_mock_Test;
};

#endif //PARSER__PARSER_H_
