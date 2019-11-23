//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PFOLLOW_H_
#define PARSER_PRIMITIVE_PFOLLOW_H_

#include "APrimitive.h"

class PFollow : public APrimitive {
 public:
  explicit PFollow(std::string text) : APrimitive(std::move(text)) {}
};

#endif //PARSER_PRIMITIVE_PFOLLOW_H_
