//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PFORK_H_
#define PARSER_PRIMITIVE_PFORK_H_

#include "ComplexPrimitive.h"

class PFork : public ComplexPrimitive {
 public:
  explicit PFork(std::string text)
      : ComplexPrimitive(std::move(text)),
        is_else(false) {}

  bool acceptScheduler(AScheduler &scheduler) const override {
    return scheduler.schedulePrimitive(*this);
  }

  void addChild(APrimitive *child) override {
    if (is_else)
      elseChildren.push_back(child);
    else
      ComplexPrimitive::addChild(child);
  }

  void startElseSection() override {
    is_else = true;
  }

  std::string toString() override {
    std::string ans = "Fork\n" + ComplexPrimitive::toString();
    return ans;
  }

  const ptrVector<APrimitive> &getElseChildren() const {
    return elseChildren;
  }

  size_t maxTextWid() const override {
    size_t lineNum = getLineNum(getInnerText());
    return getMaxTextWid(getInnerText()) + lineNum;
  }

  size_t getChildMaxWid() const {
    size_t max = 0;
    for (const auto &i : getChildren()) {
      size_t len = i->maxTextWid();
      max = std::max(len, max);
    }

    return max;
  }
  size_t getElseChildMaxWid() const {
    size_t max = 0;
    for (const auto &i : getElseChildren()) {
      size_t len = i->maxTextWid();
      max = std::max(len, max);
    }
    return max;
  }

 private:
  bool is_else;
  ptrVector<APrimitive> elseChildren;
};

#endif //PARSER_PRIMITIVE_PFORK_H_
