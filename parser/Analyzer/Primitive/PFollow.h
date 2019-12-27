//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PFOLLOW_H_
#define PARSER_PRIMITIVE_PFOLLOW_H_

#include "APrimitive.h"
#include "../../Tools/Liner.h"

class PFollow : public APrimitive {
 public:
  explicit PFollow(std::string text)
      : APrimitive(std::move(text)) {}

  bool acceptScheduler(AScheduler &scheduler) const override {
    return scheduler.schedulePrimitive(*this);
  }

  std::string toString() const override {
    return std::string("Func\n") +
        APrimitive::toString();
  }

  size_t maxTextWid() const override {
    return getMaxTextWid(getInnerText());
  }
};

#endif //PARSER_PRIMITIVE_PFOLLOW_H_
