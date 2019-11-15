//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER__PARSER_H_
#define PARSER__PARSER_H_

#include <string>
#include <vector>

#include "Analyzers/AnalyzerType.h"
#include "Schedulers/SchedulerType.h"

#include "Analyzers/AbstractAnalyzer.h"
#include "Schedulers/AbstractScheduler.h"



class Parser {
 public:
  virtual jsonString parse(const std::string &, AnalyzerType = CLike, SchedulerType = Gost);

 protected:
  virtual AbstractAnalyzer *createAnalyzer(AnalyzerType);
  virtual AbstractScheduler *createScheduler(SchedulerType);
  virtual jsonString figuresToJson(Figures figures);
};

#endif //PARSER__PARSER_H_
