//
// Created by arthur on 22.11.2019.
//

#include <memory>

#include "../../Analyzer/Primitive/ComplexPrimitive.h"
#include "EmborderScheduler.h"

#include "../Figure/FBegCycle.h"
#include "../Figure/FEndCycle.h"
#include "../Figure/FFollow.h"
#include "../Figure/FFork.h"
#include "../Figure/FFunc.h"
#include "../../Tools/Liner.h"
#include "../Figure/FLine.h"
#include "../../Tools/SizedLiner.h"

ptrVector<AFigure> EmborderScheduler::schedule(const std::unique_ptr<ComplexPrimitive> &algorithm)
{
    curState.x = meta.pageWidth() / 2;
    curState.y = meta.yMargin();
    curState.wid = meta.pageWidth() - meta.xPadding() * 2;
    curState.page = 1;

    algorithm->acceptScheduler(*this);
    return std::move(figures);
}

bool EmborderScheduler::schedulePrimitive(const PAlgorithm &pAlgorithm, AScheduler &scheduler)
{
    for (const auto &i : pAlgorithm.getChildern())
        i->acceptScheduler(*this);

    return true;
}

bool EmborderScheduler::schedulePrimitive(const PFollow &pFollow, AScheduler &scheduler)
{
    size_t ln, mw;
    Rect beforeCycleRect = XFitRect(pFollow.getInnerText());

    return true;
}

bool EmborderScheduler::schedulePrimitive(const PCycle &pCycle, AScheduler &scheduler)
{
    Rect beforeCycleRect = countEmborderRect(pCycle.getBeforeCycyleText());
    figures.push_back(new FBegCycle(beforeCycleRect, pCycle.getBeforeCycyleText()));
    curY += beforeCycleRect.height;
    figures.push_back(new FLine(Point{curX, curY}, Point{curX, curY + meta.blockSpace()}));
    curY += meta.blockSpace();

    for (const auto &i : pCycle.getChildern())
        i->acceptScheduler(*this);

    Rect afterCycleRect = countEmborderRect(pCycle.getAfterCycleText());
    figures.push_back(new FEndCycle(afterCycleRect, pCycle.getAfterCycleText()));
    curY += afterCycleRect.height;

    return true;
}

bool EmborderScheduler::schedulePrimitive(const PFork &pFork, AScheduler &scheduler)
{
    figures.push_back(new FFork(Point{0, 0}, Rect{10, 10}, pFork.getInnerText()));
    for (const auto &i : pFork.getChildern())
        i->acceptScheduler(*this);
    for (const auto &i : pFork.getElseChildren())
        i->acceptScheduler(*this);
    return true;
}

bool EmborderScheduler::schedulePrimitive(const PFunc &pFunc, AScheduler &scheduler)
{
    figures.push_back(new FFunc(Point{0, 0}, Rect{10, 10}, pFunc.getInnerText()));
    return true;
}

Rect EmborderScheduler::countEmborderRect(const std::string &text)
{
    Rect output{};
    size_t lineNumber, maxWidth;
    getTextCharacteristics(lineNumber, maxWidth, text);

    output.width = (maxWidth + 2) * meta.symbolWidth();
    output.height = (lineNumber + 1) * meta.lineHeight();
    output.center.x = curX;
    output.center.y = curY + output.height / 2;

    return output;
}

const EmborderScheduler::State &EmborderScheduler::getCurState() const
{
    return curState;
}

void EmborderScheduler::setCurState(State curState)
{
    EmborderScheduler::curState = curState;
}

// line Number MaxWidth
Rect EmborderScheduler::XFitRect(size_t &lineNum, size_t &maxWidth, std::string &text)
{
    std::string out;
    std::string line;
    SizedLiner liner(text);
    lineNum = maxWidth = 0;
    size_t neededLineWidth = curState.wid - meta.xPadding() - 1;

    while (liner.getLine(line, neededLineWidth)) {
        lineNum += 1;
        maxWidth = (maxWidth < line.size()) ? line.size() : maxWidth;
        out += line;
    }

    return Rect{curState.x, curState.y,};
}

void EmborderScheduler::getTextCharacteristics(size_t &lineNumber, size_t &maxWidth, const std::string &text)
{
    std::string line;
    Liner liner(text);
    lineNumber = maxWidth = 0;

    while (liner.getLine(line)) {
        lineNumber += 1;
        maxWidth = (line.size() > maxWidth) ? line.size() : maxWidth;
    }
}

size_t EmborderScheduler::getBlockSize(const std::string &text)
{
    return (text.size() + meta.xPadding()) * meta.symbolWidth();
}
