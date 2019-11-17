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
                         const std::shared_ptr<BaseAnalyzer> &analyzer,
                         const std::shared_ptr<AbstractScheduler> &scheduler) {

  Primitives primitives = analyzer->analyze(text);
  Figures figures = scheduler->schedule(primitives);

  jsonString retJson = figuresToJson(figures);
  return retJson;
}

jsonString Parser::figuresToJson(const Figures &figures) {
  jsonString retVal;
  for (const auto &i: figures) {
    retVal += i->toJson();
  }
  return retVal;
}
