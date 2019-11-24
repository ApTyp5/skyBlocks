//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZER_H_
#define PARSER_ANALYZER_INDENTANALYZER_H_

#include <memory>

#include "Alphabet/PythonLikeAlphabet.h"
#include "../AAnalyzer.h"
#include "../Primitive/ComplexPrimitive.h"
#include "../Primitive/PFollow.h"
#include "../Primitive/PFork.h"
#include "../Primitive/PCycle.h"
#include "../Primitive/PFunc.h"

#include "Tools/States.h"
#include "Tools/Memory.h"

class IndentAnalyzer : public AAnalyzer {
 public:
  explicit IndentAnalyzer(ptrVector<Error> &errors) : AAnalyzer(errors), AlphaBet(new PythonLikeAlphabet) {}
  ComplexPrimitive *analyze(std::string text, size_t line_num) override;

 private:
  virtual bool emptyStringPhase(const std::string &line, size_t line_num);
  virtual bool indentCheckPhase(const std::string &line, size_t line_num);
  virtual bool analyzeStrPhase(const std::string &line, size_t line_num);

 private:
  std::string retIndent(const std::string &line);
  const std::string &getCurrentIndent();
  void mergeBackMemory();

 private:
  bool tryAddPFollowToLastMem();
  bool tryMemorizePFork();
  bool tryMemorizePCycle();
  bool addPFuncToLastMem(std::string name, std::string text);

 private:
  State state_;
  std::string indent;
  std::string shortMemory;
  ptrVector<Memory> longMemory;
  std::unique_ptr<BaseAlphabet> AlphaBet;
};

#endif //PARSER_ANALYZER_INDENTANALYZER_H_
