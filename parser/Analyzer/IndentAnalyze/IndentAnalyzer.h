//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZER_H_
#define PARSER_ANALYZER_INDENTANALYZER_H_

#include <memory>

#include "../AAnalyzer.h"
#include "../Primitive/ComplexPrimitive.h"
#include "../Primitive/PFollow.h"
#include "../Primitive/PFork.h"
#include "../Primitive/PCycle.h"
#include "States.h"

struct Memory {
  State state_;
  std::string indent;
  ComplexPrimitive *complexPrimitive;

  Memory(State state, std::string indent, ComplexPrimitive *complex_primitive) :
      state_(state), indent(std::move(indent)), complexPrimitive(complex_primitive) {}

/*  Memory(const Memory &memory){
    state_ = memory.state_;
    indent = memory.indent;
    complexPrimitive = new ComplexPrimitive(memory.complexPrimitive);
  }    */

  Memory(Memory &&memory) noexcept {
    state_ = memory.state_;
    indent = std::move(memory.indent);
    complexPrimitive = memory.complexPrimitive;
    memory.complexPrimitive = nullptr;
  }

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
  ComplexPrimitive *analyze(std::string text, size_t line_num) override;
 private:
  virtual bool emptyStringPhase(const std::string &line, size_t line_num);
  virtual bool indentCheckPhase(const std::string &line, size_t line_num);
  virtual bool analyzeStrPhase(const std::string &line, size_t line_num);

  std::string retIndent(const std::string &line);
 private:
  State state_;
  std::string indent;
  std::string shortMemory;
  ptrVector<Memory> longMemory;
};

#endif //PARSER_ANALYZER_INDENTANALYZER_H_
