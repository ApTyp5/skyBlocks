//
// Created by arthur on 15.11.2019.
//

#ifndef PARSER_MOCKS_MOCKANALYZER_H_
#define PARSER_MOCKS_MOCKANALYZER_H_

#include "../Analyzers/BaseAnalyzer.h"
#include "gmock/gmock.h"

class MockAnalyzer : public BaseAnalyzer {
 public:
  MOCK_METHOD(Primitives, analyze, (std::string), (override));
 protected:
  void followHandler(std::string line) override {}
  void ifHandler(std::string line) override {}
  void whileHandler(std::string line) override {}

};

#endif //PARSER_MOCKS_MOCKANALYZER_H_
