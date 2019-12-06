//
// Created by arthur on 22.11.2019.
//

#include <iostream>
#include "IndentAnalyzer.h"
#include "../Primitive/PAlgorithm.h"
#include "../../Tools/Liner.h"
#include "Tools/IndentAnalyzerUtils.h"


ComplexPrimitive *IndentAnalyzer::analyze(std::string text, size_t frontLine, size_t backLine)
{
    state_ = State::UnknownIndent;
    indent = shortMemory = "";

    std::string line;
    Liner liner(text);
    liner.skipLines(frontLine - 1);

    liner.getLine(line);
    if (isDef(line)) {
        std::string name;
        IndentAnalyzerUtils::extractSecondWord(name, line, AlphaBet->WordDelimiters());
        initAlg(name);
        liner.getLine(line);
    }
    else {
        initAlg("__main__");
    }

    for (size_t lineNum = frontLine; lineNum < backLine; lineNum++, liner.getLine(line)) {
        if (emptyStringPhase(line, frontLine)) continue;
        if (indentCheckPhase(line, frontLine)) continue;
        if (analyzeStrPhase(line, frontLine)) continue;
    }

    flushShortMemory();

    while (longMemory.size() > 1)
        mergeBackMemory();

    return longMemory.pop_back()->getComplexPrimitive();
}

bool IndentAnalyzer::emptyStringPhase(const std::string &line, size_t lineNum)
{
    std::string curIndent = retIndent(line);

    if (line.front() == '\n' || curIndent.size() + 1 == line.size()) {
        switch (state_) {
            case State::Follow:tryAddPFollowToLastMem();
                return true;

            case State::Fork:
                if (tryMemorizePFork()) {
                    state_ = State::UnknownIndent;
                }
                else {
                    push_error("empty fork body", lineNum, 0);
                }
                return true;

            case State::Cycle:
                if (tryMemorizePCycle()) {
                    state_ = State::UnknownIndent;
                }
                else {
                    push_error("empty cycle body", lineNum, 0);
                }
                return true;
            case State::UnknownIndent:return true;
            case State::Alg:throw "Alg stage in emptyStringPhase";
            default:throw "default case in emptyStringPhase";
        }
    }

    return false;
}

bool IndentAnalyzer::indentCheckPhase(const std::string &line, size_t lineNum)
{
    std::string lineIndent = retIndent(line);

    switch (state_) {
        case State::Alg:; // state_ = UnknownIndent;
        case State::UnknownIndent:longMemory.back()->setBodyIndent(lineIndent);
            state_ = State::Follow;
            return false;

        case State::Follow:
            if (lineIndent == getCurrentIndent())
                return false;

            while (longMemory.size() != 1) {
                tryAddPFollowToLastMem();

                if (longMemory.back()->getState() == State::Fork) {
                    std::string str = IndentAnalyzerUtils::cutFront(line, lineIndent.size());
                    std::string fWord;
                    bool isMultWords = IndentAnalyzerUtils::extractFirstWord(fWord, str, AlphaBet->WordDelimiters());
                    IndentAnalyzerUtils::delLastNewLine(fWord);
                    if (fWord == AlphaBet->ElseWord()) {
                        longMemory.back()->getComplexPrimitive()->startElseSection();
                        state_ = State::UnknownIndent;
                        if (isMultWords) {
                            push_error("text after else word ignored", lineNum,
                                       lineIndent.size() + AlphaBet->ElseWord().size() + 1);
                        }
                        return true;
                    }
                }

                mergeBackMemory();
                if (lineIndent == getCurrentIndent())
                    return false;
            }

            push_error("indent does not match any of previous", lineNum);
            return false;

        case State::Fork:
            if (lineIndent == getCurrentIndent())
                return false;
            if (!tryMemorizePFork()) {
                push_error("empty fork body", lineNum);
            }
            state_ = State::UnknownIndent;
            break;

        case State::Cycle:
            if (lineIndent == getCurrentIndent())
                return false;
            if (!tryMemorizePCycle()) {
                push_error("empty cycle body", lineNum);
            }
            state_ = State::UnknownIndent;
            break;

        default:throw "indent check default case phase";
    }

    longMemory.back()->setBodyIndent(lineIndent);
    state_ = State::Follow;
    return false;
}

bool IndentAnalyzer::analyzeStrPhase(const std::string &line, size_t line_num)
{
    const std::string &currentIndent = getCurrentIndent();
    std::string lineWithoutIndent = IndentAnalyzerUtils::cutFront(line, currentIndent.size());

    switch (state_) {
        case State::Fork:
        case State::Cycle:shortMemory += lineWithoutIndent;
            return false;

        case State::Alg: throw "Alg state in analyzeStrPhase";
        case State::UnknownIndent: throw "Alg state in analyzeStrPhase";
        default: throw "default case in analyzeStrPhase";

        case State::Follow:std::string fstWord;
            std::string others;
            IndentAnalyzerUtils::delimString(fstWord, others, lineWithoutIndent, AlphaBet->WordDelimiters());

            bool isFork = fstWord == AlphaBet->ForkWord();
            bool isCycle = fstWord == AlphaBet->CycleWord();

            if (isFork || isCycle) {
                tryAddPFollowToLastMem();
                state_ = isFork ? (State::Fork) : (State::Cycle);
                // set While or Fork indent
                setWFIndent(fstWord.size(), others.size(), currentIndent, lineWithoutIndent);
                shortMemory += others;
                return false;
            }

            if (fstWord == AlphaBet->CallFuncWord()) {
                tryAddPFollowToLastMem();
                addPFuncToLastMem(others);
                return false;
            }

            shortMemory += lineWithoutIndent;
    }
    return false;
}

void IndentAnalyzer::setWFIndent(size_t fstWordSize, size_t othersWordSize,
                                 const std::string &lineIndent,
                                 const std::string &lineWithoutIndent)
{
    size_t LWISize = lineWithoutIndent.size();
    size_t n = LWISize - othersWordSize - fstWordSize;
    std::string end = lineWithoutIndent.substr(fstWordSize, n);
    std::string begin = IndentAnalyzerUtils::strAppendMultipleSymbols(
        lineIndent, AlphaBet->WordDelimiters().front(), fstWordSize);
    indent = begin + end;
}

std::string IndentAnalyzer::retIndent(const std::string &line)
{
    std::string retVal;
    auto i = line.cbegin();
    while (IndentAnalyzerUtils::isInVector(*i, AlphaBet->WordDelimiters())) {
        retVal.push_back(*i);
        i++;
    }

    return retVal;
}

bool IndentAnalyzer::tryAddPFollowToLastMem()
{
    if (!shortMemory.empty()) {
        IndentAnalyzerUtils::delLastNewLine(shortMemory);
        longMemory.back()->getComplexPrimitive()->addChild(new PFollow(shortMemory));
        shortMemory.clear();
        return true;
    }
    return false;
}

bool IndentAnalyzer::tryMemorizePFork()
{
    if (!shortMemory.empty()) {
        IndentAnalyzerUtils::delLastNewLine(shortMemory);
        longMemory.push_back(new Memory(State::Fork, new PFork(shortMemory)));
        shortMemory.clear();
        return true;
    }
    return false;
}

bool IndentAnalyzer::tryMemorizePCycle()
{
    if (!shortMemory.empty()) {
        std::string topText, botText;
        IndentAnalyzerUtils::delimString(topText, botText, shortMemory, AlphaBet->SectionDelimiters());
        IndentAnalyzerUtils::delLastNewLine(topText);
        IndentAnalyzerUtils::delLastNewLine(botText);
        topText = IndentAnalyzerUtils::skipBorderSymbols(topText, AlphaBet->WordDelimiters());
        botText = IndentAnalyzerUtils::skipBorderSymbols(botText, AlphaBet->WordDelimiters());

        longMemory.push_back(new Memory(State::Cycle, new PCycle(topText, botText)));
        shortMemory.clear();
        return true;
    }
    return false;
}

void IndentAnalyzer::mergeBackMemory()
{
    Memory *last = longMemory.pop_back();
    longMemory.back()->merge(last);
}

const std::string &IndentAnalyzer::getCurrentIndent()
{
    if (state_ == State::UnknownIndent
        || state_ == State::Alg)
        throw std::exception();

    if (state_ == State::Fork
        || state_ == State::Cycle)
        return indent;

    return longMemory.back()->getBodyIndent();
}

bool IndentAnalyzer::addPFuncToLastMem(std::string text)
{
    std::string name;
    std::string otherPart;
    IndentAnalyzerUtils::delimString(name, otherPart, text, AlphaBet->WordDelimiters());
    IndentAnalyzerUtils::delLastNewLine(otherPart);

    longMemory.back()->getComplexPrimitive()->addChild(new PFunc(std::move(name), std::move(otherPart)));
    return true;
}

IndentAnalyzer::IndentAnalyzer(ptrVector<ParseError> &errors, BaseAlphabet *alphabet)
    : AAnalyzer(errors), AlphaBet(alphabet)
{}

void IndentAnalyzer::flushShortMemory()
{
    emptyStringPhase("\n", 0);
}
bool IndentAnalyzer::isDef(const std::string &line)
{
    const std::string &defFW = AlphaBet->DefineFuncWord();
    return line.substr(0, defFW.size()) == defFW;
}
void IndentAnalyzer::initAlg(const std::string &name)
{
    longMemory.push_back(new Memory(State::Alg, new PAlgorithm(name)));
}

