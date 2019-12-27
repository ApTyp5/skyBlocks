//
// Created by arthur on 22.11.2019.
//

#include <memory>
#include <utility>
#include <cassert>

#include "../../Analyzer/Primitive/PAlgorithm.h"
#include "GostScheduler.h"

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
#include "../Figure/FBegEnd.h"
#include "../../Analyzer/IndentAnalyze/Tools/States.h"

ptrVector<AFigure> GostScheduler::schedule(const std::unique_ptr<PAlgorithm> &root) {
  size_t wid = root->maxTextWid();
  size_t maxW = meta.pw() - 2 * meta.xp();

  curState = State(meta.pw() / 2,
                   meta.yp(),
                   std::min(maxW, wid),
                   maxW,
                   1);

  root->acceptScheduler(*this);

  //Удаляем все линии с конца

  while (figures.size() > 0 && figures.back()->isSingleMeasureFigure())
    delete figures.pop_back();

  // Если на верхнем уровне имеются открывающий / закрывающий
  // блоки следования, то они преобразуюстя в терминальные блоки
  if (FFollow::onOneLine(figures.back(), figures[0])) {
    castFFollowToFBegEnd(figures[0]);
    castFFollowToFBegEnd(figures.back());
  }

  return std::move(figures);
}

bool GostScheduler::schedulePrimitive(const PAlgorithm &pAlgorithm) {

  for (const auto &i : pAlgorithm.getChildren())
    i->acceptScheduler(*this);
  return true;
}
bool GostScheduler::schedulePrimitive(const PFollow &pFollow) {
  addFigure(FigureType::Follow, pFollow.getInnerText());
  return true;
}
bool GostScheduler::schedulePrimitive(const PCycle &pCycle) {
  addFigure(FigureType::BegCycle, pCycle.getBeforeCycyleText());

  for (const auto &i : pCycle.getChildren())
    i->acceptScheduler(*this);

  addFigure(FigureType::EndCycle, pCycle.getAfterCycleText());
  return true;
}
bool GostScheduler::schedulePrimitive(const PFunc &pFunc) {
  addFigure(FigureType::Func, pFunc.getName() + pFunc.getInnerText());
  return true;
}

bool GostScheduler::schedulePrimitive(const PFork &pFork) {
  double negX = (curState.x() + meta.xp()) / 2;
  double posX = 2 * curState.x() - negX;
  size_t maxWid = curState.maxWid() / 2;
  size_t chldMaxWid = pFork.getChildMaxWid();
  size_t elseChldMaxWid = pFork.getElseChildMaxWid();

  addFFork(pFork.getInnerText(), negX, posX);
  State old = getCurState();

  State negState(old);
  negState.setX(negX);
  negState.setMaxWid(pFork.getChildMaxWid());
  negState.setW(std::min(maxWid, elseChldMaxWid));
  negState.setMaxWid(maxWid);
  CurState() = negState;

  for (const auto &i : pFork.getElseChildren())
    i->acceptScheduler(*this);
  negState = getCurState();

  State posState(old);
  posState.setX(posX);
  posState.setW(std::min(maxWid, chldMaxWid));
  posState.setMaxWid(maxWid);
  CurState() = posState;
  for (const auto &i : pFork.getChildren())
    i->acceptScheduler(*this);
  posState = getCurState();

  connectForkParts(negState, posState);
  curState.setY(posState.y());
  curState.setX(old.x());
  curState.setW(old.width());
  pushSpaceLine("");

  return true;
}

sRect GostScheduler::rectForkFixedSize(std::string &text) {
  size_t lineNum, maxWidth = curState.maxWid();
  size_t curMaxWidth = 0;
  std::string line;
  std::string output;
  SizedLiner liner(text);
  lineNum = 0;

  while (liner.getLine(line, maxWidth, true)) {
    curMaxWidth = std::max(curMaxWidth, line.size());
    lineNum += 1;
    output += line;
  }

  text = output;
  text.pop_back(); // удаление \n

  sRect outRect{(getCurState().width() + lineNum * 2) * meta.sw() + 2 * meta.xp(),
                (lineNum + curMaxWidth / 4) * meta.lh() + 2 * meta.yp()};
  return outRect;
}

sRect GostScheduler::rectXFixedSize(std::string &text) {
  size_t lineNum, maxWidth = curState.maxWid();
  std::string line;
  std::string output;
  SizedLiner liner(text);
  lineNum = 0;

  while (liner.getLine(line, maxWidth, true)) {
    lineNum += 1;
    output += line;
  }

  text = output;
  text.pop_back(); // удаление \n

  sRect outRect{getCurState().width() * meta.sw() + 2 * meta.xp(), lineNum * meta.lh() + 2 * meta.yp()};
  return outRect;
}
sRect GostScheduler::continueBlockSize() {
  sRect size{};
  size.h = size.w = std::max(meta.sw(), meta.lh()) * 2;
  return size;
}
void GostScheduler::initNewPage(size_t page) {
  CurState().setPage(CurState().page() + 1);
}
void GostScheduler::addFigure(FigureType type, const std::string &innerText) {
  assert(type != FigureType::Fork);
  std::string text(innerText);
  sRect widthFitRect = rectXFixedSize(text);

  checkPageEnd(widthFitRect);
  Rect figRect{curState.x(), curState.y() + widthFitRect.h / 2, widthFitRect};
  pushFigure(type, figRect, text, curState.page());
  pushSpaceLine();
}
void GostScheduler::addFFork(const std::string &innerText, double leftX, double rightX) {
  std::string text(innerText);
  sRect widthFitRect = rectForkFixedSize(text);

  checkPageEnd(widthFitRect);
  Rect forkRect{curState.x(), curState.y() + widthFitRect.h / 2, widthFitRect};
  pushFigure(FigureType::Fork, forkRect, text, curState.page());
  pushForkLines(forkRect, leftX, rightX);
  curState.setY(curState.y() + meta.bs());
}
void GostScheduler::pushForkLines(Rect forkRect, double leftX, double rightX) {
  double halfWidth = forkRect.size.w / 2;
  double leftBorder = forkRect.center.x - halfWidth;

  Point hrombusLeftAngle{leftBorder, forkRect.center.y};
  Point hrombusRightAngle{leftBorder + forkRect.size.w, forkRect.center.y};

  Point leftMid{leftX, hrombusLeftAngle.y};
  Point rightMid{rightX, hrombusRightAngle.y};

  Point leftLast{leftMid.x, leftMid.y + forkRect.size.h / 2 + meta.bs()};
  Point rightLast{rightMid.x, rightMid.y + forkRect.size.h / 2 + meta.bs()};

  figures.push_back(new FLine(hrombusLeftAngle, leftMid, "", curState.page()));
  figures.push_back(new FLine(leftMid, leftLast, "", curState.page()));

  figures.push_back(new FLine(hrombusRightAngle, rightMid, "Yes", curState.page()));
  figures.push_back(new FLine(rightMid, rightLast, "", curState.page()));
}
void GostScheduler::connectForkParts(State &negState, State &posState) {
  if (negState.page() > posState.page()) {
    CurState() = posState;
    gotoPage(negState.page());
    posState = getCurState();
  } else if (posState.page() > negState.page()) {
    CurState() = negState;
    gotoPage(posState.page());
    negState = getCurState();
  }

  if (negState.y() > posState.y()) {
    CurState() = posState;
    pushVerticalLine(posState.x(), posState.y(), negState.y(), posState.page());
    posState = getCurState();
  } else if (posState.y() > negState.y()) {
    CurState() = negState;
    pushVerticalLine(negState.x(), negState.y(), posState.y(), posState.page());
    negState = getCurState();
  }

  pushHorizLine(curState.y(), negState.x(), posState.x(), posState.page());
}
bool GostScheduler::isYFit(double h) {
  size_t neededSpace = curState.y() + h + meta.bs() + continueBlockSize().h;
  return neededSpace <= getBotBorder();
}
bool GostScheduler::isYFit(sRect rect) {
  return GostScheduler::isYFit(rect.h);
}
void GostScheduler::checkPageEnd(sRect widthFitRect) {
  if (!isYFit(widthFitRect))
    gotoPage(curState.page() + 1);
}
void GostScheduler::pushHorizLine(double y, double xLeft, double xRight, size_t page, std::string text) {
  figures.push_back(new FLine(Point{xLeft, y}, Point{xRight, y}, std::move(text), page));
}
void GostScheduler::pushVerticalLine(double x, double yTop, double yBot, size_t page, std::string text) {
  figures.push_back(new FLine(Point{x, yTop}, Point{x, yBot}, std::move(text), page));
  curState.setY(yBot);
}
void GostScheduler::pushFigure(FigureType type, Rect rect, std::string text, size_t page) {
  figures.push_back(FigureCreator::createDMF(type, rect, std::move(text), page));
  curState.setY(curState.y() + rect.size.h);
}
void GostScheduler::pushSpaceLine(std::string text) {// Предполагается, что размеры проверены заранее
  figures.push_back(new FLine(Point{curState.x(), curState.y()},
                              Point{curState.x(), curState.y() + meta.bs()},
                              std::move(text), curState.page()));

  curState.setY(curState.y() + meta.bs());
}
void GostScheduler::pushContinueFigure() {
  sRect contBlockRectSize = continueBlockSize();
  Rect continueRect{curState.x(), curState.y() + contBlockRectSize.h / 2, contBlockRectSize};
  figures.push_back(new FContinue(continueRect, curState.page()));
  curState.setY(curState.y() + contBlockRectSize.h);
}
const GostScheduler::State &GostScheduler::getCurState() const {
  return curState;
}
GostScheduler::State &GostScheduler::CurState() {
  return curState;
}
void GostScheduler::gotoPage(size_t page) {
  pushContinueFigure();
  curState.setY(meta.ym());
  curState.setPage(page);
  pushContinueFigure();
  pushSpaceLine();
}
void GostScheduler::addPadding(sRect &rect) {
  rect.w += 2 * meta.xp();
  rect.h += 2 * meta.yp();
}
void GostScheduler::castFFollowToFBegEnd(AFigure *&figure) {
  auto *begin = new FBegEnd(*dynamic_cast<FFollow *>(figure));
  delete figure;
  figure = begin;
}

double GostScheduler::State::x() const {
  return _x;
}
void GostScheduler::State::setX(double x) {
  State::_x = x;
}
double GostScheduler::State::y() const {
  return _y;
}
void GostScheduler::State::setY(double y) {
  State::_y = y;
}
double GostScheduler::State::width() const {
  return _w;
}
void GostScheduler::State::setW(double w) {
  State::_w = w;
}
size_t GostScheduler::State::page() const {
  return _page;
}
void GostScheduler::State::setPage(double page) {
  State::_page = page;
}
GostScheduler::State::State(size_t x, size_t y, size_t w, size_t mW, size_t page)
    : _x(x), _y(y), _w(w), _maxW(mW), _page(page) {}
double GostScheduler::State::maxWid() const {
  return _maxW;
}
void GostScheduler::State::setMaxWid(double max_w) {
  _maxW = max_w;
}
