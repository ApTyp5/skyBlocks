//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER__PARSER_H_
#define PARSER__PARSER_H_

#include <string>
#include <vector>
#include <memory>

#include "Analyzers/AnalyzerType.h"
#include "Schedulers/SchedulerType.h"

#include "Analyzers/BaseAnalyzer.h"
#include "Schedulers/AbstractScheduler.h"


class Parser {
 public:
  jsonString parse(const std::string &,
                   const std::shared_ptr<BaseAnalyzer> &analyzer,
                   const std::shared_ptr<AbstractScheduler> &scheduler);

 protected:
  jsonString figuresToJson(const Figures &figures);

};

#endif //PARSER__PARSER_H_
