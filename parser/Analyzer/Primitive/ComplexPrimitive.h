//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_
#define PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_

#include "APrimitive.h"
#include "../../ptrVector.h"

class ComplexPrimitive : public APrimitive {
 public:
  explicit ComplexPrimitive(std::string text) : APrimitive(std::move(text)) {}
  virtual void addChild(APrimitive *child) {
    children.push_back(child);
  }

 protected:
  ptrVector<APrimitive> children;
};

#endif //PARSER_PRIMITIVE_COMPLEXPRIMITIVE_H_
