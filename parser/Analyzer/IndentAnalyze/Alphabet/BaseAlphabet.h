//
// Created by arthur on 24.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_ALPHABET_BASEALPHABET_H_
#define PARSER_ANALYZER_INDENTANALYZE_ALPHABET_BASEALPHABET_H_

#include <utility>
#include <vector>
#include <string>

class BaseAlphabet {
 public:
  BaseAlphabet(std::string forkWord, std::string elseWord, std::string cycleWord,
               std::string callFuncWord, std::string defineFuncWord,
               std::vector<char> wordDelimiters, std::vector<char> sectionDelimiters) :
      forkWord(std::move(forkWord)),
      elseWord(std::move(elseWord)),
      cycleWord(std::move(cycleWord)),
      callFuncWord(std::move(callFuncWord)),
      defineFuncWord(std::move(defineFuncWord)),
      wordDelimiters(std::move(wordDelimiters)),
      sectionDelimiters(std::move(sectionDelimiters)) {}

  virtual const std::vector<char> &WordDelimiters() { return wordDelimiters; }
  virtual const std::vector<char> &SectionDelimiters() { return sectionDelimiters; }
  virtual const std::string &ForkWord() { return forkWord; }
  virtual const std::string &ElseWord() { return elseWord; }
  virtual const std::string &CycleWord() { return cycleWord; }
  virtual const std::string &CallFuncWord() { return callFuncWord; }
  virtual const std::string &DefineFuncWord() { return defineFuncWord; }

 private:
  std::vector<char> sectionDelimiters;
  std::vector<char> wordDelimiters;
  std::string forkWord;
  std::string elseWord;
  std::string cycleWord;
  std::string callFuncWord;
  std::string defineFuncWord;
};
#endif //PARSER_ANALYZER_INDENTANALYZE_ALPHABET_BASEALPHABET_H_
