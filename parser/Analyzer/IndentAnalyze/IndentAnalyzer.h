//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZER_H_
#define PARSER_ANALYZER_INDENTANALYZER_H_

#include <memory>

#include "../AAnalyzer.h"
#include "../Primitive/ComplexPrimitive.h"
#include "../Primitive/PCycle.h"
#include "../Primitive/PFollow.h"
#include "../Primitive/PFork.h"
#include "../Primitive/PFunc.h"
#include "Alphabet/PythonLikeAlphabet.h"
#include "Tools/Memory.h"
#include "Tools/States.h"

class FixtureIndentAnalyzer;
class FixtureIndentAnalyzer_get_current_indent_follow_test;

class IndentAnalyzer: public AAnalyzer
{
public:
    explicit IndentAnalyzer(ptrVector<Error> &errors);
    ComplexPrimitive *analyze(std::string text, size_t line_num) override;

private:
    virtual bool emptyStringPhase(const std::string &line, size_t line_num);
    virtual bool indentCheckPhase(const std::string &line, size_t line_num);
    virtual bool analyzeStrPhase(const std::string &line, size_t line_num);

private:
    std::string retIndent(const std::string &line);
    const std::string &getCurrentIndent();
    void mergeBackMemory();
    void flushShortMemory();

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

    friend class FixtureIndentAnalyzer;
    friend class FixtureIndentAnalyzer_get_current_indent_Test;
    friend class FixtureIndentAnalyzer_ret_indent_Test;
    friend class FixtureIndentAnalyzer_merge_back_mem_Test;
    friend class FixtureIndentAnalyzer_try_add_pfollow_positive_Test;
};

#endif //PARSER_ANALYZER_INDENTANALYZER_H_
