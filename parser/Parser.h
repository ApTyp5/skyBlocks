//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER__PARSER_H_
#define PARSER__PARSER_H_

#include <string>
#include <vector>
#include <memory>

#include "Error/Error.h"

typedef std::string jsonString;

class Parser {
 public:
  jsonString parse(const std::string &,
                   const std::shared_ptr<BaseAnalyzer> &analyzer,
                   const std::shared_ptr<AbstractScheduler> &scheduler);

 protected:
  jsonString formJson(const Figures &figures);

};

#endif //PARSER__PARSER_H_
