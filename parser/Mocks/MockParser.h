//
// Created by arthur on 15.11.2019.
//

#ifndef PARSER_MOCKS_MOCKPARSER_H_
#define PARSER_MOCKS_MOCKPARSER_H_

#include "../Parser.h"
#include "MockAnalyzer.h"
#include "MockScheduler.h"

class MockParser : public Parser {
 public:
  jsonString parse(const std::string &text = "", AnalyzerType = CLike,
                   SchedulerType = Gost) override {
    return Parser::parse(text);
  }

 protected:
  AbstractAnalyzer *createAnalyzer(AnalyzerType) override {
    return new MockAnalyzer;
  }

  AbstractScheduler *createScheduler(SchedulerType) override {
    return new MockSheduler;
  };

  MOCK_METHOD(jsonString, figuresToJson, (Figures), (override));
};
#endif //PARSER_MOCKS_MOCKPARSER_H_
