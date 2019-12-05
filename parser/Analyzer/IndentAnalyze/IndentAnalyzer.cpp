//
// Created by arthur on 22.11.2019.
//

#include <iostream>
#include "IndentAnalyzer.h"
#include "../Primitive/PAlgorithm.h"
#include "../../Tools/Liner.h"
#include "Tools/IndentAnalyzerUtils.h"
#include "../../Scheduler/Figure/FigureTypes.h"


ComplexPrimitive *IndentAnalyzer::analyze(std::string text, size_t frontLine, size_t backLine)
{
    longMemory.push_back(new Memory(State::Alg, new PAlgorithm("__main__")));
    state_ = State::UnknownIndent;
    indent = shortMemory = "";
    Liner liner(text);
    std::string line;


    for (size_t i = 0; i < frontLine; i++, liner.getLine(line));
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

bool IndentAnalyzer::emptyStringPhase(const std::string &line, size_t line_num)
{
    std::string curIndent = retIndent(line);

    if (line.front() == '\n' || curIndent.size() + 1 == line.size()) {
        switch (state_) {
            case State::Follow:tryAddPFollowToLastMem();
                return true;

            case State::Fork:
                if (tryMemorizePFork()) {
                    state_ = State::Follow;
                }
                return true;

            case State::Cycle:
                if (tryMemorizePCycle()) {
                    state_ = State::Follow;
                }
                return true;
            case State::UnknownIndent:return true;
            case State::Alg:
            default:throw std::exception();
        }
    }

    return false;
}

bool IndentAnalyzer::indentCheckPhase(const std::string &line, size_t line_num)
{
    std::string lineIndent = retIndent(line);

    switch (state_) {
        case State::Alg:; // state_ = UnknownIndent;
        case State::UnknownIndent:longMemory.back()->setBodyIndent(lineIndent);
            state_ = State::Follow;
            return false;

        case State::Follow:
            while (longMemory.size() != 1) {
                if (lineIndent == getCurrentIndent())
                    return false;

                tryAddPFollowToLastMem();

                if (longMemory.back()->getState() == State::Fork) {
                    std::string str = IndentAnalyzerUtils::skipSymbols(line, AlphaBet->WordDelimiters());
                    if (str.substr(0, AlphaBet->ElseWord().size()) == AlphaBet->ElseWord()) {
                        longMemory.back()->getComplexPrimitive()->startElseSection();
                        state_ = State::UnknownIndent;
                        return true;
                    }
                }
                mergeBackMemory();
            }

            /* error */
            return false;

        case State::Fork:if (lineIndent == getCurrentIndent()) return false;
            if (!tryMemorizePFork()) {/* error */}
            state_ = State::UnknownIndent;
            break;

        case State::Cycle:if (lineIndent == getCurrentIndent()) return false;
            if (!tryMemorizePCycle()) {/* error */}
            state_ = State::UnknownIndent;
            break;

        default: throw std::exception();
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

        case State::Alg:
        case State::UnknownIndent:
        default: throw std::exception();

        case State::Follow:std::string fstWord;
            std::string others;
            IndentAnalyzerUtils::retFirstWord(fstWord, others, lineWithoutIndent);

            bool isFork = fstWord == AlphaBet->ForkWord();
            bool isCycle = fstWord == AlphaBet->CycleWord();

            if (isFork || isCycle) {
                tryAddPFollowToLastMem();

                state_ = isFork ? (State::Fork) : (State::Cycle);
                std::string addIndent = retIndent(others);
                others = IndentAnalyzerUtils::cutFront(others, addIndent.size());

                indent = IndentAnalyzerUtils::strAppendMultipleSymbols(
                    currentIndent,
                    AlphaBet->WordDelimiters().front(),
                    isFork ? AlphaBet->ForkWord().size() : AlphaBet->CycleWord().size()
                ) + addIndent;

                shortMemory += others;
                return false;
            }

            if (fstWord == AlphaBet->CallFuncWord()) {
                tryAddPFollowToLastMem();
                addPFuncToLastMem(fstWord, others);
                return false;
            }

            shortMemory += lineWithoutIndent;
    }
    return false;
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
        longMemory.back()->getComplexPrimitive()->addChild(new PFollow(shortMemory));
        shortMemory.clear();
        return true;
    }
    return false;
}

bool IndentAnalyzer::tryMemorizePFork()
{
    if (!shortMemory.empty()) {
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
        IndentAnalyzerUtils::extractCycleParts(topText, botText, shortMemory);

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

bool IndentAnalyzer::addPFuncToLastMem(std::string name, std::string text)
{
    longMemory.back()->getComplexPrimitive()->addChild(new PFunc(std::move(name), std::move(text)));
    return true;
}

IndentAnalyzer::IndentAnalyzer(ptrVector<ParseError> &errors, BaseAlphabet *alphabet)
    : AAnalyzer(errors), AlphaBet(alphabet)
{}

void IndentAnalyzer::flushShortMemory()
{
    emptyStringPhase("\n", 0);
}

