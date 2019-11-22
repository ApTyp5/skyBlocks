//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PCYCLE_H_
#define PARSER_PRIMITIVE_PCYCLE_H_

#include <utility>

#include "ComplexPrimitive.h"

class PCycle : public ComplexPrimitive {
 public:
  PCycle(std::string beginCycleText, std::string endCycleText) :
      ComplexPrimitive(std::move(beginCycleText)),
      endCycleText(std::move(endCycleText)) {}
 private:
  std::string endCycleText;
};

#endif //PARSER_PRIMITIVE_PCYCLE_H_
