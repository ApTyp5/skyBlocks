//
// Created by arthur on 23.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_TOOLS_UTILS_H_
#define PARSER_ANALYZER_INDENTANALYZE_TOOLS_UTILS_H_

#include "../../Primitive/APrimitive.h"
#include "../States.h"
#include "../../Primitive/PAlgorithm.h"
#include "../../Primitive/PFollow.h"
#include "../../Primitive/PFork.h"
#include "../../Primitive/PCycle.h"

class Utils {
 public:
  static APrimitive *createPrimitive(State state,
                                     const std::string &par1 = "",
                                     const std::string &par2 = "") {
    switch (state) {
      case Alg:return new PAlgorithm(par1, par2);
      case Follow: return new PFollow(par1);
      case Fork: return new PFork(par1);
      case Cycle: return new PCycle(par1, par2);
    }
  };

  static std::string extractAlgName(std::string &addText, const std::string &text) {
    int first_space = text.find(' ');
    if (first_space < 0)
      return text;

    addText = text.substr(first_space);
    std::string name = text.substr(0, first_space);
    return name;
  }
};

#endif //PARSER_ANALYZER_INDENTANALYZE_TOOLS_UTILS_H_
