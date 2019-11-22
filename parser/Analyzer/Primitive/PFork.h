//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PFORK_H_
#define PARSER_PRIMITIVE_PFORK_H_

#include "ComplexPrimitive.h"

class PFork : public ComplexPrimitive {
 public:
  explicit PFork(std::string text) : ComplexPrimitive(std::move(text)) {}

 private:
  ptrVector<APrimitive> elseChildren;
};

#endif //PARSER_PRIMITIVE_PFORK_H_
