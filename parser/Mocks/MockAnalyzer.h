//
// Created by arthur on 15.11.2019.
//

#ifndef PARSER_MOCKS_MOCKANALYZER_H_
#define PARSER_MOCKS_MOCKANALYZER_H_

#include "../Analyzers/AbstractAnalyzer.h"
#include "gmock/gmock.h"

class MockAnalyzer : public AbstractAnalyzer {
 public:
  MOCK_METHOD(Primitives, analyze, (std::string), (override));
};

#endif //PARSER_MOCKS_MOCKANALYZER_H_
