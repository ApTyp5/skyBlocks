//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZER_H_
#define PARSER_ANALYZER_INDENTANALYZER_H_

#include <memory>

#include "../AAnalyzer.h"
#include "../Primitive/ComplexPrimitive.h"

enum State {
  Alg,
  Unknown,
  Follow,
  Fork,
  Cycle,
};

struct Memory {
  State state_;
  std::string indent;
  ComplexPrimitive *complexPrimitive;

  Memory(State state, std::string indent, ComplexPrimitive *complex_primitive) :
      state_(state), indent(std::move(indent)), complexPrimitive(complex_primitive) {}

  void merge(Memory *memory) {
    if (memory == nullptr)
      throw std::exception();

    complexPrimitive->addChild(memory->complexPrimitive);
    memory->complexPrimitive = nullptr;
    delete memory;
  }
};

class IndentAnalyzer : public AAnalyzer {
 public:
  ComplexPrimitive *analyze(ptrVector<Error> &errors, std::string text) override;
 private:
  bool emptyStringPhase(std::string line);
  bool indentCheckPhase(std::string line);
  bool analyzeStrPhase(std::string line);
 private:
  State state_;
  std::string indent;
  std::string shortMemory;
  ptrVector<Memory> longMemory;
};

#endif //PARSER_ANALYZER_INDENTANALYZER_H_
