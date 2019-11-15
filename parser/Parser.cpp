//
// Created by arthur on 09.11.2019.
//

#include "Analyzers/AnalyzerType.h"
#include "Analyzers/ClikeAnalyzer.h"
#include "Schedulers/SchedulerType.h"
#include "Schedulers/GostScheduler.h"
#include "Parser.h"

#include <memory>

jsonString Parser::parse(const std::string &text,
                         AnalyzerType analyzer_type,
                         SchedulerType scheduler_type) {

  std::unique_ptr<AbstractAnalyzer> analyzer(createAnalyzer(analyzer_type));
  std::unique_ptr<AbstractScheduler> scheduler(createScheduler(scheduler_type));

  Primitives primitives = analyzer->analyze(text);
  Figures figures = scheduler->schedule(primitives);

  jsonString retValue = figuresToJson(figures);
  return retValue;
}

AbstractAnalyzer *Parser::createAnalyzer(AnalyzerType type) {
  switch (type) {
    case AnalyzerType::CLike: return new ClikeAnalyzer;
    default: return nullptr;
  }
}

AbstractScheduler *Parser::createScheduler(SchedulerType type) {
  switch (type) {
    case SchedulerType::Gost: return new GostScheduler;
    default: return nullptr;
  }
}

jsonString Parser::figuresToJson(const Figures figures) {
  jsonString retVal;
  for (const auto &i: figures) {
    retVal += i->toJson();
  }
  return retVal;
}
