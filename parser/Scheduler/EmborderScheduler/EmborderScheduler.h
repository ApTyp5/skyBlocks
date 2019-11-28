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
    struct State
    {
        // cur bottom x, cur bottom y, cur width
        size_t x, y, w;
        // cur page num
        size_t page;
    };

protected:
    sRect rectXFitSize(std::string &text);
    sRect continueBlockSize();

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

    // Дополниельные функции
    bool isYFit(sRect rect);
    bool isYFit(size_t h = 0);
    void initNewPage(size_t page = 1);
    void checkPageEnd(sRect widthFitRect);
    void connectForkParts(State negState, State posState);
    void gotoPage(size_t page);

protected:
    State curState{};

protected:
    const State &getCurState() const;
    void setCurState(State curState);
};

#endif //PARSER_SCHEDULER_COMMONSCHEDULER_H_
