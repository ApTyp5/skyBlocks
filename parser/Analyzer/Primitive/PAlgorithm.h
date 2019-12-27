//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PALGORITHM_H_
#define PARSER_PRIMITIVE_PALGORITHM_H_

#include "ComplexPrimitive.h"

class PAlgorithm: public ComplexPrimitive
{
public:
    explicit PAlgorithm(std::string text)
        :
        ComplexPrimitive(std::move(text))
    {}

  bool acceptScheduler(AScheduler &scheduler) const override {
    return scheduler.schedulePrimitive(*this);
  }

  std::string toString() override {
    std::string ans = "Algorithm\n" + ComplexPrimitive::toString();
    return ans;
  }
  size_t maxTextWid() const override {
    size_t maxWid = 0;
    for (const auto &i : children) {
      size_t chldWid = i->maxTextWid();
      maxWid = std::max(maxWid, chldWid);
    }
    return maxWid;
  }
};

#endif //PARSER_PRIMITIVE_PALGORITHM_H_
