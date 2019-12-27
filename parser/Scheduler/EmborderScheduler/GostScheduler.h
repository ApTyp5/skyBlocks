//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_COMMONSCHEDULER_H_
#define PARSER_SCHEDULER_COMMONSCHEDULER_H_

#include "../AScheduler.h"
#include "../../Analyzer/Primitive/PAlgorithm.h"
#include "../../Analyzer/Primitive/PCycle.h"
#include "../../Analyzer/Primitive/PFollow.h"
#include "../../Analyzer/Primitive/PFork.h"
#include "../../Analyzer/Primitive/PFunc.h"
#include "../Figure/FigureTypes.h"
#include "../../Scheduler/Figure/Primitives/Rect.h"

class GostScheduler : public AScheduler {
 public:
  explicit GostScheduler(const Meta &meta)
      : AScheduler(meta), curState(0, 0, 0, 0, 0) {}
  ptrVector<AFigure> schedule(const std::unique_ptr<PAlgorithm> &root) override;

  bool schedulePrimitive(const PAlgorithm &pAlgorithm) override;
  bool schedulePrimitive(const PCycle &pCycle) override;
  bool schedulePrimitive(const PFollow &pFollow) override;
  bool schedulePrimitive(const PFork &pFork) override;
  bool schedulePrimitive(const PFunc &pFunc) override;

 protected:
  class State {
    // cur bottom x, cur bottom y, cur width
    double _x, _y, _w;
    size_t _maxW;
    // cur page num
    size_t _page;
   public:
    double maxWid() const;

   public:
    void setMaxWid(double max_w);
    explicit State(size_t x = 0, size_t y = 0, size_t w = 0, size_t mW = 0, size_t page = 0);
    double x() const;
    double y() const;
    double width() const;
    size_t page() const;
    void setX(double x);
    void setY(double y);
    void setW(double w);
    void setPage(double page);
  };

    State curState;
  const State &getCurState() const;
  State &CurState();

protected:
    // add* - Добавление с проверкой размеров
    void addFigure(FigureType type, const std::string &innerText);
    void addFFork(const std::string &innerText, double leftX, double rightX);

    // push* - Добавление
    void pushFigure(FigureType type, Rect rect, std::string text, size_t page);
    void pushSpaceLine(std::string text = "");
    void pushForkLines(Rect forkRect, double leftX, double rightX);
    void pushHorizLine(double y, double xLeft, double xRight, size_t page = 1, std::string text = "");
    void pushVerticalLine(double x, double yTop, double yBot, size_t page = 1, std::string text = "");
    void pushContinueFigure();

    // Add ones
    bool isYFit(sRect rect);
    bool isYFit(double h = 0);
    void initNewPage(size_t page = 1);
    void checkPageEnd(sRect widthFitRect);
    void connectForkParts(State &negState, State &posState);
    void gotoPage(size_t page);
    void addPadding(sRect &rect);

  sRect rectXFixedSize(std::string &text);
  sRect continueBlockSize();
    void castFFollowToFBegEnd(AFigure *&figure);

    friend class FEmborderScheduler;
    friend class FEmborderScheduler_rectXFitSizeWithoutMarginGoodWidth_Test;
    friend class FEmborderScheduler_rectXFitSizeWithoutMarginBadWidth_Test;
    friend class FEmborderScheduler_rectXFitSizeWithMarginBadWidth_Test;
    friend class FEmborderScheduler_rectXFitSizeWithMarginGoodWidth_Test;
    friend class FEmborderScheduler_pushContinueFigure_Test;
    friend class FEmborderScheduler_pushVerticalLine_Test;
    friend class FEmborderScheduler_pushSpaceLine_Test;
    friend class FEmborderScheduler_pushForkLines_Test;
    friend class FEmborderScheduler_connectForkPartsLeftPageLess_Test;
    friend class FEmborderScheduler_connectForkPartsRightPageLess_Test;
    friend class FEmborderScheduler_addFigureCommon_Test;
    friend class FEmborderScheduler_addFigureBadWidth_Test;
    friend class FEmborderScheduler_addFigureTooTight_Test;
    friend class FEmborderScheduler_addForkCommon_Test;
    friend class FEmborderScheduler_addForkBadWidth_Test;
    friend class FEmborderScheduler_addForkTooTight_Test;
};

#endif //PARSER_SCHEDULER_COMMONSCHEDULER_H_
