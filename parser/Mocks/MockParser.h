//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_MOCKS_MOCKPARSER_H_
#define PARSER_MOCKS_MOCKPARSER_H_

#include <gmock/gmock.h>

#include "../Parser.h"

class MockParser: public Parser
{
public:
    //MOCK_METHOD(jsonString, parse, (std::string text, AAnalyzeFactory *analyzeFactory, AScheduler *scheduler), (override));
    MOCK_METHOD(jsonString, parseFunc, (std::string
        text, std::string
        name, AAnalyzeFactory * analyzeFactory, AScheduler * scheduler), (override));
};

#endif //PARSER_MOCKS_MOCKPARSER_H_
