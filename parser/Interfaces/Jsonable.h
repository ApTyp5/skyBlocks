//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_INTERFACES_JSONABLE_H_
#define PARSER_INTERFACES_JSONABLE_H_

#include <string>

typedef std::string jsonString;

class Jsonable{
 public:
  virtual jsonString toJson() const = 0;
};

#endif //PARSER_INTERFACES_JSONABLE_H_
