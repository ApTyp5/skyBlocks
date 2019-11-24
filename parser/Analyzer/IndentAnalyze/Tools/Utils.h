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

  static std::string cutFront(const std::string &str, size_t size) {
    return str.substr(size);
  }

  static bool extractFuncName(std::string &name,
                              std::string &otherText,
                              const std::string &text,
                              char delim = ' ') {
    return separateString(name, otherText, text, delim);
  }

  static bool extractCycleParts(std::string &topPart,
                                std::string &botPart,
                                const std::string &text,
                                char delim = ';') {
    return separateString(topPart, botPart, text, delim);
  }

  static bool retFirstWord(std::string &firstWord, std::string &others, const std::string &str) {
    return separateString(firstWord, others, str, ' ');
  }

 private:
  static bool separateString(std::string &firstPart,
                             std::string &secondPart,
                             const std::string &initString,
                             char delim) {
    int first_delim = initString.find(delim);
    if (first_delim < 0) {
      firstPart = initString;
      return false;
    }

    firstPart = initString.substr(0, first_delim);
    secondPart = initString.substr(first_delim + 1);
    return true;
  }
};

#endif //PARSER_ANALYZER_INDENTANALYZE_TOOLS_UTILS_H_
