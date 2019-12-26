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

class FIndentPythonLikeAnalyzer;
class FixtureIndentAnalyzer_get_current_indent_follow_test;

class IndentAnalyzer: public AAnalyzer
{
public:
    explicit IndentAnalyzer(ptrVector<ParseError> &errors, BaseIndentAlphabet *alphabet);
    ComplexPrimitive *analyze(std::wstring text, size_t frontLine, size_t backLine) override;

private:
    virtual bool emptyStringPhase(const std::wstring &line, size_t lineNum);
    virtual bool indentCheckPhase(const std::wstring &line, size_t lineNum);
    virtual bool analyzeStrPhase(const std::wstring &line, size_t line_num);

private:
    std::wstring retIndent(const std::wstring &line);
    const std::wstring &getCurrentIndent();
    void mergeBackMemory();
    void flushShortMemory();

private:
    bool tryAddPFollowToLastMem();
    bool tryMemorizePFork();
    bool tryMemorizePCycle();
    bool addPFuncToLastMem(std::wstring text);
    bool isDef(const std::wstring &line);
    void initAlg(const std::wstring &name);
private:
    State state_;
    std::wstring indent;
    std::wstring shortMemory;
    ptrVector<Memory> longMemory;
    std::unique_ptr<BaseIndentAlphabet> AlphaBet;

    friend class FIndentPythonLikeAnalyzer;
    friend class FIndentPythonLikeAnalyzer_get_current_indent_Test;
    friend class FIndentPythonLikeAnalyzer_ret_indent_Test;
    friend class FIndentPythonLikeAnalyzer_merge_back_mem_Test;
    friend class FIndentPythonLikeAnalyzer_try_add_pfollow_positive_Test;
    friend class FIndentPythonLikeAnalyzer_try_add_pfollow_positive_Test;
    friend class FIndentPythonLikeAnalyzer_is_def_positive_Test;
    friend class FIndentPythonLikeAnalyzer_is_def_negative_Test;
    friend class FIndentPythonLikeAnalyzer_is_def_negative2_Test;
    void setWFIndent(size_t fstWordSize,
                     size_t othersWordSize,
                     const std::wstring &lineIndent,
                     const std::wstring &lineWithoutIndent);
};

#endif //PARSER_ANALYZER_INDENTANALYZER_H_
