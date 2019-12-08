//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_MOCKS_MOCKANALYZEFACTORY_H_
#define PARSER_MOCKS_MOCKANALYZEFACTORY_H_

#include <gmock/gmock.h>

#include "../Analyzer/AAnalyzeFactory.h"

class MockAnalyzeFactory: public AAnalyzeFactory
{
public:
    MOCK_METHOD(AConstraintor *, createConstraintor, (ptrVector<ParseError> & ), (override));
    MOCK_METHOD(AAnalyzer *, createAnalyzer, (ptrVector<ParseError> & ), (override));
};

#endif //PARSER_MOCKS_MOCKANALYZEFACTORY_H_


