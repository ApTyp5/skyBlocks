//
// Created by arthur on 22.11.2019.
//

#include "IndentAnalyzer.h"

#include "../Primitive/PAlgorithm.h"
#include "Tools/Liner.h"
#include "Tools/Utils.h"

ComplexPrimitive *IndentAnalyzer::analyze(std::string text, size_t line_num) {
  ptrVector<APrimitive> retVal;
  longMemory.push_back(new Memory(Alg, "", new PAlgorithm("__main__", "")));
  indent = shortMemory = "";
  Liner liner(text);
  std::string line;
  line_num -= 1;

  while (liner.getLine(line)) {
    line_num += 1;
    if (emptyStringPhase(line, line_num)) continue;
    if (indentCheckPhase(line, line_num)) continue;
    if (analyzeStrPhase(line, line_num)) continue;
  }

  while (longMemory.size() > 1)
    longMemory.back()->merge(longMemory.pop_back());

  return longMemory.pop_back()->complexPrimitive;
}

bool IndentAnalyzer::emptyStringPhase(const std::string &line, size_t line_num) {
  std::string curIndent = retIndent(line);
  if (line.front() == '\n' || curIndent.size() + 1 == line.size()) {

    if (state_ == Follow) {
      if (!shortMemory.empty()) {
        longMemory.back()->complexPrimitive->addChild(new PFollow(shortMemory));
        shortMemory.clear();
      }
      return true;
    }

    if (shortMemory.empty()) push_error("unexpected empty string", line_num);

    switch (state_) {
      case Alg:
        if (!shortMemory.empty()) {
          std::string name, addText;
          name = Utils::extractAlgName(addText, line);
          longMemory.push_back(new Memory(state_,))
        }

      case Fork:
      case Cycle:

      case Follow:
        if (!shortMemory.empty()) {
          longMemory.back()->complexPrimitive->addChild(new PFollow(shortMemory));
          shortMemory.clear();
        }
        break;

      default: throw std::exception();
    }
  }
  return false;
}

bool IndentAnalyzer::indentCheckPhase(const std::string &line, size_t line_num) {
  std::string lineIndent = retIndent(line);
  switch (state_) {
    case Alg: state_ = Unknown;
    case Unknown:state_ = Follow;
      indent = lineIndent;
      break;

    case Follow:
      if (lineIndent == indent) {

      }

    case Fork:
    case Cycle:
      if (indent == lineIndent)
        shortMemory += line.substr(lineIndent.size());
      else {
        size_t delim_pos = shortMemory.find(';');
        ComplexPrimitive *cycle = new PCycle(
            shortMemory.substr(0, delim_pos),
            shortMemory.substr(delim_pos + 1)
        );

        longMemory.push_back(new Memory(state_, lineIndent, cycle));
        state_ = Follow;
        indent = lineIndent;
      }
  }

  return false;
}

std::string IndentAnalyzer::retIndent(const std::string &line) {
  std::string retVal;
  auto i = line.cbegin();
  while (*i == ' ' || *i == '\t') {
    retVal.push_back(*i);
    i++;
  }

  return retVal;
}
