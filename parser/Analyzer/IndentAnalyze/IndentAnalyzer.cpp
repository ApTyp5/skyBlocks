//
// Created by arthur on 22.11.2019.
//

#include "IndentAnalyzer.h"
#include "../Primitive/PAlgorithm.h"
#include "Tools/Liner.h"

ComplexPrimitive *IndentAnalyzer::analyze(ptrVector<Error> &errors, std::string text) {
  ptrVector<APrimitive> retVal;
  longMemory.push_back(new Memory(Alg, "", new PAlgorithm("__main__", "")));
  indent = shortMemory = "";
  Liner liner(text);
  std::string line;

  while (liner.getLine(line)) {
    if (emptyStringPhase(line)) continue;
    if (indentCheckPhase(line)) continue;
    if (analyzeStrPhase(line)) continue;
  }

  while (longMemory.size() > 1)
    longMemory.back()->merge(longMemory.pop_back());

  return longMemory.pop_back()->complexPrimitive;
}
bool IndentAnalyzer::emptyStringPhase(std::string line) {
  if (line.front() == '\n') {
    switch (state_) {
      case Alg:break;
      case Unknown:break;
      case Follow:break;
      case Fork:break;
      case Cycle:break;
      default: throw std::exception();
    }
  }
}
