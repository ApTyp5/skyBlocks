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

class EmborderScheduler: public AScheduler
{
public:
    explicit EmborderScheduler(const Meta &meta)
        : AScheduler(meta)
    {}
    ptrVector<AFigure> schedule(const std::unique_ptr<ComplexPrimitive> &algorithm) override;

    bool schedulePrimitive(const PAlgorithm &pAlgorithm, AScheduler &scheduler) override;
    bool schedulePrimitive(const PCycle &pCycle, AScheduler &scheduler) override;
    bool schedulePrimitive(const PFollow &primitive, AScheduler &scheduler) override;
    bool schedulePrimitive(const PFork &pFork, AScheduler &scheduler) override;
    bool schedulePrimitive(const PFunc &pFunc, AScheduler &scheduler) override;

protected:
    struct State
    {
        size_t x, y, wid;
        size_t page;
    };

    Rect countEmborderRect(const std::string &text);
    void getTextCharacteristics(size_t &lineNumber, size_t &maxWidth, const std::string &text);

protected:
    Rect XFitRect(size_t &lineNum, size_t &maxWidth, std::string &text);

protected:
    size_t getBlockSize(const std::string &text);
    State curState;

protected:
    const State &getCurState() const;
    void setCurState(State curState);

};

#endif //PARSER_SCHEDULER_COMMONSCHEDULER_H_
