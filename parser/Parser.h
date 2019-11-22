//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER__PARSER_H_
#define PARSER__PARSER_H_

#include <string>
#include <vector>
#include <memory>

#include "Error/Error.h"
#include "JsonFormer/JsonFormer.h"
#include "Stubs/Stubs.h"
#include "ptrVector.h"


class Parser {
 public:
  explicit Parser(DataBaseConnection connection) {}
  jsonString parse(std::string text, Meta meta,
                   std::unique_ptr<AAnalyzeFactory> &analyzeFactory,
                   std::unique_ptr<AScheduler> &scheduler) {
    return formJson();
  }
  jsonString parseFunc(std::string text, std::string name, Meta meta,
                       std::unique_ptr<AAnalyzeFactory> &analyzeFactory,
                       std::unique_ptr<AScheduler> &scheduler) {
    return formJson();
  }

 protected:
  jsonString formJson() {
    return jsonString();
  }

 private:
  DataBaseConnection connection;
  ptrVector<Error> errors;

};

#endif //PARSER__PARSER_H_
