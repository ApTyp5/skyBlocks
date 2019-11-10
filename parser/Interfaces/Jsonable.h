//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_INTERFACES_JSONABLE_H_
#define PARSER_INTERFACES_JSONABLE_H_

#include <string>

class Jsonable{
 public:
  virtual std::string toJson() const = 0;
};

#endif //PARSER_INTERFACES_JSONABLE_H_
