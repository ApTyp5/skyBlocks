//
// Created by arthur on 22.11.2019.
//

#include "IndentAnalyzer.h"
#include "../Primitive/PAlgorithm.h"
#include "Tools/Liner.h"
#include "Tools/Utils.h"


ComplexPrimitive *IndentAnalyzer::analyze(std::string text, size_t line_num)
{
    longMemory.push_back(new Memory(Alg, new PAlgorithm("__main__", "")));
    indent = shortMemory = "";
    Liner liner(text);
    std::string line;
    line_num -= 1;
    state_ = UnknownIndent;

    while (liner.getLine(line)) {
        line_num += 1;
        if (emptyStringPhase(line, line_num)) continue;
        if (indentCheckPhase(line, line_num)) continue;
        if (analyzeStrPhase(line, line_num)) continue;
    }

    while (longMemory.size() > 1)
        mergeBackMemory();

    return longMemory.pop_back()->getComplexPrimitive();
}

bool IndentAnalyzer::emptyStringPhase(const std::string &line, size_t line_num)
{
    std::string curIndent = retIndent(line);

    if (line.front() == '\n' || curIndent.size() + 1 == line.size()) {
        switch (state_) {
            case Follow:tryAddPFollowToLastMem();
                break;

            case Fork:
                if (tryMemorizePFork()) {
                    state_ = Follow;
                }
                break;

            case Cycle:
                if (tryMemorizePCycle()) {
                    state_ = Follow;
                }
                break;
            case UnknownIndent: break;
            case Alg:throw std::exception();
            default: throw std::exception();
        }
    }
    return true;
}

bool IndentAnalyzer::indentCheckPhase(const std::string &line, size_t line_num)
{
    std::string lineIndent = retIndent(line);

    switch (state_) {
        case Alg:; // state_ = UnknownIndent;
        case UnknownIndent:longMemory.back()->setIndent(lineIndent);
            state_ = Follow;
            return false;

        case Follow:
            while (longMemory.size() != 0) {
                if (lineIndent == longMemory.back()->getIndent())
                    return false;
                tryAddPFollowToLastMem();
                mergeBackMemory();
            }
            /* error */
            return false;

        case Fork:if (lineIndent == indent) break;
            if (!tryMemorizePFork()) {/* error */}
            state_ = UnknownIndent;
            return true;

        case Cycle:if (lineIndent == indent) break;
            if (!tryMemorizePCycle()) {/* error */}
            state_ = UnknownIndent;
            return true;

        default: throw std::exception();
    }

    return false;
}

bool IndentAnalyzer::analyzeStrPhase(const std::string &line, size_t line_num)
{
    const std::string &currentIndent = getCurrentIndent();
    std::string lineWithoutIndent = Utils::cutFront(line, currentIndent.size());

    switch (state_) {
        case Fork:
        case Cycle:shortMemory += lineWithoutIndent;
            return false;

        case Alg:
        case UnknownIndent:
        default: throw std::exception();

        case Follow:std::string fstWord;
            std::string others;
            Utils::retFirstWord(fstWord, others, lineWithoutIndent);

            bool isFork = fstWord == AlphaBet->ForkWord();
            bool isCycle = fstWord == AlphaBet->CycleWord();

            if (isFork || isCycle) {
                tryAddPFollowToLastMem();

                state_ = isFork ? Fork : Cycle;
                indent = Utils::makeIncreasedIndent(
                    currentIndent,
                    AlphaBet->WordDelimiters().front(),
                    AlphaBet->ForkWord().size()
                );

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
    while (Utils::isInVector(*i, AlphaBet->WordDelimiters())) {
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
        longMemory.push_back(new Memory(Fork, new PFork(shortMemory)));
        shortMemory.clear();
        return true;
    }
    return false;
}

bool IndentAnalyzer::tryMemorizePCycle()
{
    if (!shortMemory.empty()) {
        std::string topText, botText;
        Utils::extractCycleParts(topText, botText, shortMemory);

        longMemory.push_back(new Memory(Cycle, new PCycle(topText, botText)));
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
    if (state_ == UnknownIndent
        || state_ == Alg)
        throw std::exception();

    if (state_ == Fork
        || state_ == Cycle)
        return indent;

    return longMemory.back()->getIndent();
}

bool IndentAnalyzer::addPFuncToLastMem(std::string name, std::string text)
{
    longMemory.back()->getComplexPrimitive()->addChild(new PFunc(std::move(name), std::move(text)));
    return true;
}

