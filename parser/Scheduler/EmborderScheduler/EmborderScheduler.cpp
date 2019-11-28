//
// Created by arthur on 22.11.2019.
//

#include <memory>
#include <utility>
#include <cassert>

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
#include "../Figure/FContinue.h"
#include "../Figure/FigureCreator.h"
#include "../Figure/SingleMeasureFigure.h"
#include "../Figure/FBegin.h"
#include "../Figure/FEnd.h"

ptrVector<AFigure> EmborderScheduler::schedule(const std::unique_ptr<ComplexPrimitive> &primitives)
{
    initNewPage(1);
    primitives->acceptScheduler(*this);

    while (dynamic_cast<SingleMeasureFigure *>(figures.back()))
        delete figures.pop_back();

    if (dynamic_cast<FFollow *>(figures[0]))
        figures[0] = dynamic_cast<FBegin *>(figures[0]);

    if (dynamic_cast<FFollow *>(figures.back()))
        figures.back() = dynamic_cast<FEnd *>(figures.back());

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
    addFigure(FigureType::Follow, pFollow.getInnerText());
    return true;
}
bool EmborderScheduler::schedulePrimitive(const PCycle &pCycle, AScheduler &scheduler)
{
    addFigure(FigureType::EndCycle, pCycle.getBeforeCycyleText());

    for (const auto &i : pCycle.getChildern())
        i->acceptScheduler(*this);

    addFigure(FigureType::BegCycle, pCycle.getAfterCycleText());
    return true;
}
bool EmborderScheduler::schedulePrimitive(const PFunc &pFunc, AScheduler &scheduler)
{
    addFigure(FigureType::Func, pFunc.getInnerText());
    return true;
}
bool EmborderScheduler::schedulePrimitive(const PFork &pFork, AScheduler &scheduler)
{
    size_t negX = (curState.x() - meta.xm()) / 2;
    size_t posX = curState.x() + negX;
    addFFork(pFork.getInnerText(), negX, posX);
    State old = getCurState();

    State negState(old);
    negState.setX(negX);
    negState.setW(negState.width() / 2);
    setCurState(negState);
    for (const auto &i : pFork.getChildern())
        i->acceptScheduler(*this);

    State posState(old);
    posState.setX(negX);
    posState.setW(posState.width() / 2);
    setCurState(posState);
    for (const auto &i : pFork.getElseChildren())
        i->acceptScheduler(*this);

    connectForkParts(negState, posState);
    setCurState(posState);
    curState.setX(old.x());
    curState.setW(old.width());

    return true;
}
sRect EmborderScheduler::rectXFitSize(std::string &text, bool withMargin)
{
    std::string line;
    std::string output;
    SizedLiner liner(text);
    size_t lineNum, maxWidth;
    lineNum = maxWidth = 0;
    size_t neededLineWidth = curState.width();

    while (liner.getLine(line, neededLineWidth, true)) {
        lineNum += 1;
        size_t withoutLF = line.size() - 1;
        maxWidth = (maxWidth < withoutLF) ? withoutLF : maxWidth;
        output += line;
    }

    text = output;
    sRect outRect{maxWidth * meta.sw(), lineNum * meta.lh()};
    if (withMargin) {
        outRect.w += 2 * meta.xm();
        outRect.h += 2 * meta.ym();
    }

    return outRect;
}
sRect EmborderScheduler::continueBlockSize()
{
    sRect size{};
    size.h = size.w = std::max(meta.sw(), meta.lh()) * 3;
    return size;
}
void EmborderScheduler::initNewPage(size_t page)
{
    setCurState(State(meta.pw() / 2, meta.yp(), meta.pw() - meta.xp() * 2, page));
}
void EmborderScheduler::addFigure(FigureType type, const std::string &innerText)
{
    assert(type != Fork);
    std::string text(innerText);
    sRect widthFitRect = rectXFitSize(text, true);

    checkPageEnd(widthFitRect);
    Rect figRect{curState.x(), curState.y() + widthFitRect.h / 2, widthFitRect};
    pushFigure(FigureCreator::createDMF(type, figRect, text, curState.page()));
    pushSpaceLine();
}
void EmborderScheduler::addFFork(const std::string &innerText, size_t leftX, size_t rightX)
{
    std::string text(innerText);
    sRect widthFitRect = rectXFitSize(text, false);
    widthFitRect *= 2;
    addMargin(widthFitRect);

    checkPageEnd(widthFitRect);
    Rect forkRect{curState.x(), curState.y() + widthFitRect.h / 2, widthFitRect};
    pushFigure(FigureCreator::createDMF(FigureType::Fork, forkRect, text, curState.page()));
    pushForkLines(forkRect, leftX, rightX);
}
void EmborderScheduler::pushForkLines(Rect forkRect, size_t leftX, size_t rightX)
{
    size_t halfWidth = forkRect.size.w / 2;
    size_t leftBorder = forkRect.center.x - halfWidth;

    Point hrombusLeftAngle{leftBorder, forkRect.center.y};
    Point hrombusRightAngle{leftBorder + forkRect.size.w, forkRect.center.y};

    Point leftMid{leftX, hrombusLeftAngle.y};
    Point rightMid{rightX, hrombusRightAngle.y};

    Point leftLast{leftMid.x, leftMid.y + forkRect.size.h / 2 + meta.bs()};
    Point rightLast{rightMid.x, rightMid.y + forkRect.size.h / 2 + meta.bs()};

    figures.push_back(new FLine(hrombusLeftAngle, leftMid, "", curState.page()));
    figures.push_back(new FLine(leftMid, leftLast, "", curState.page()));

    figures.push_back(new FLine(hrombusRightAngle, rightMid, "Да", curState.page()));
    figures.push_back(new FLine(rightMid, rightLast, "", curState.page()));
}
void EmborderScheduler::connectForkParts(State negState, State posState)
{
    if (negState.page() > posState.page()) {
        setCurState(posState);
        gotoPage(negState.page());
        posState = getCurState();
    }
    else if (posState.page() > negState.page()) {
        setCurState(negState);
        gotoPage(posState.page());
        negState = getCurState();
    }

    if (negState.y() > posState.y())
        pushVerticalLine(posState.x(), posState.y(), negState.y(), posState.page());
    else if (posState.y() > negState.y())
        pushVerticalLine(negState.x(), negState.y(), posState.y(), posState.page());

    pushHorizLine(curState.y(), negState.x(), posState.x(), posState.page());
}
bool EmborderScheduler::isYFit(size_t h)
{
    size_t neededSpace = curState.y() + h + meta.bs() + continueBlockSize().h;
    return neededSpace <= getBotBorder();
}
bool EmborderScheduler::isYFit(sRect rect)
{
    return EmborderScheduler::isYFit(rect.h);
}
void EmborderScheduler::checkPageEnd(sRect widthFitRect)
{
    if (!isYFit(widthFitRect))
        gotoPage(curState.page() + 1);
}
void EmborderScheduler::pushHorizLine(size_t y, size_t xLeft, size_t xRight, size_t page, std::string text)
{
    figures.push_back(new FLine(Point{xLeft, y}, Point{xRight, y}, std::move(text), page));
}
void EmborderScheduler::pushVerticalLine(size_t x, size_t yTop, size_t yBot, size_t page, std::string text)
{
    figures.push_back(new FLine(Point{x, yTop}, Point{x, yBot}, std::move(text), page));
    curState.setY(yBot);
}
void EmborderScheduler::pushFigure(AFigure *newFigure)
{
    figures.push_back(newFigure);
}
void EmborderScheduler::pushSpaceLine(std::string text)
{// Предполагается, что размеры проверены заранее
    figures.push_back(new FLine(Point{curState.x(), curState.y()},
                                Point{curState.x(), curState.y() + meta.bs()}, std::move(text), curState.page()));

    curState.setY(curState.y() + meta.bs());
}
void EmborderScheduler::pushContinueFigure()
{
    sRect contBlockRectSize = continueBlockSize();
    Rect continueRect{curState.x(), curState.y() + contBlockRectSize.h / 2, contBlockRectSize};
    figures.push_back(new FContinue(continueRect, curState.page()));
    curState.setY(curState.y() + contBlockRectSize.h);
}
const EmborderScheduler::State &EmborderScheduler::getCurState() const
{
    return curState;
}
void EmborderScheduler::setCurState(State curState)
{
    EmborderScheduler::curState = curState;
}
void EmborderScheduler::gotoPage(size_t page)
{
    pushContinueFigure();
    curState.setY(meta.yp());
    curState.setPage(page);
    pushContinueFigure();
    pushSpaceLine();
}
void EmborderScheduler::addMargin(sRect &rect)
{
    rect.w += 2 * meta.xm();
    rect.h += 2 * meta.ym();
}
size_t EmborderScheduler::State::x() const
{
    return _x;
}
void EmborderScheduler::State::setX(size_t x)
{
    State::_x = x;
}
size_t EmborderScheduler::State::y() const
{
    return _y;
}
void EmborderScheduler::State::setY(size_t y)
{
    State::_y = y;
}
size_t EmborderScheduler::State::width() const
{
    return _w;
}
void EmborderScheduler::State::setW(size_t w)
{
    State::_w = w;
}
size_t EmborderScheduler::State::page() const
{
    return _page;
}
void EmborderScheduler::State::setPage(size_t page)
{
    State::_page = page;
}
EmborderScheduler::State::State(size_t x, size_t y, size_t w, size_t page)
    : _x(x), _y(y), _w(w), _page(page)
{}
