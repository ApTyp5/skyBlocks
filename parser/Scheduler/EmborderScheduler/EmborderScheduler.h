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

class EmborderScheduler: public AScheduler
{
public:
    explicit EmborderScheduler(const Meta &meta)
        : AScheduler(meta)
    {}
    ptrVector<AFigure> schedule(const std::unique_ptr<ComplexPrimitive> &primitives) override;

    bool schedulePrimitive(const PAlgorithm &pAlgorithm, AScheduler &scheduler) override;
    bool schedulePrimitive(const PCycle &pCycle, AScheduler &scheduler) override;
    bool schedulePrimitive(const PFollow &primitive, AScheduler &scheduler) override;
    bool schedulePrimitive(const PFork &pFork, AScheduler &scheduler) override;
    bool schedulePrimitive(const PFunc &pFunc, AScheduler &scheduler) override;

protected:
    class State
    {
        // cur bottom x, cur bottom y, cur width
        size_t _x, _y, _w;
        // cur page num
        size_t _page;

    public:
        explicit State(size_t x = 0, size_t y = 0, size_t w = 0, size_t page = 0);
        size_t x() const;
        size_t y() const;
        size_t width() const;
        size_t page() const;
        void setX(size_t x);
        void setY(size_t y);
        void setW(size_t w);
        void setPage(size_t page);
    };

    State curState;
    const State &getCurState() const;
    void setCurState(State curState);

protected:
    // add* - Добавление с проверкой размеров
    void addFigure(FigureType type, const std::string &innerText);
    void addFFork(const std::string &innerText, size_t leftX, size_t rightX);

    // push* - Добавление
    void pushFigure(AFigure *newFigure);
    void pushSpaceLine(std::string text = "");
    void pushForkLines(Rect forkRect, size_t leftX, size_t rightX);
    void pushHorizLine(size_t y, size_t xLeft, size_t xRight, size_t page = 1, std::string text = "");
    void pushVerticalLine(size_t x, size_t yTop, size_t yBot, size_t page = 1, std::string text = "");
    void pushContinueFigure();

    // Add ones
    bool isYFit(sRect rect);
    bool isYFit(size_t h = 0);
    void initNewPage(size_t page = 1);
    void checkPageEnd(sRect widthFitRect);
    void connectForkParts(State negState, State posState);
    void gotoPage(size_t page);
    void addMargin(sRect &rect);

    sRect rectXFitSize(std::string &text, bool withMargin = true);
    sRect continueBlockSize();

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
};

#endif //PARSER_SCHEDULER_COMMONSCHEDULER_H_
