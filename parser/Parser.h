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


class Parser {
 public:
  Parser(DataBaseConnection connection);

 private:
  DataBaseConnection connection;
  std::vector

};

#endif //PARSER__PARSER_H_
