//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_ANALYZERS_BASEANALYZER_H_
#define PARSER_ANALYZERS_BASEANALYZER_H_

#include <vector>
#include <memory>

#include "AnalyzerType.h"
#include "../Primitives/AbstractPrimitive.h"

typedef std::vector<std::shared_ptr<AbstractPrimitive>> Primitives;

class BaseAnalyzer {
  enum State {
    Follow,
    While,
    If,
  };
  struct Chunk {
    State state_;
    size_t counter;
    std::string buf;
    Primitives primitives_;
  };

 public:
  virtual Primitives analyze(std::string text);
  static std::shared_ptr<BaseAnalyzer> createAnalyzer(AnalyzerType);

 protected:
  virtual void followHandler(std::string line) = 0;
  virtual void ifHandler(std::string line) = 0;
  virtual void whileHandler(std::string line) = 0;

 protected:
  bool cont;
  Chunk chunk_;
  std::vector<Chunk> stack;
};

#endif //PARSER_ANALYZERS_BASEANALYZER_H_
