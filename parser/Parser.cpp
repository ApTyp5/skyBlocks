//
// Created by arthur on 09.11.2019.
//

#include "Analyzers/AnalyzerType.h"
#include "Parser.h"

AbstractAnalyzer *Parser::createAnalyzer(AnalyzerType) {
  return nullptr;
}
AbstractScheduler *Parser::createScheduler(SchedulerType) {
  return nullptr;
}
std::string Parser::figuresToJson(std::vector<Jsonable *> figures) {
  return std::string();
}
std::string Parser::parse(std::string, AnalyzerType, SchedulerType) {
  return std::string();
}
