//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_ASCHEDULER_H_
#define PARSER_SCHEDULER_ASCHEDULER_H_

/*
#include "../Analyzer/Primitive/APrimitive.h"
#include "../Analyzer/Primitive/PAlgorithm.h"
#include "../Analyzer/Primitive/PCycle.h"
#include "../Analyzer/Primitive/PFollow.h"
#include "../Analyzer/Primitive/PFork.h"
#include "../Analyzer/Primitive/PFunc.h"
*/
#include <memory>

#include "../Tools/ptrVector.h"
#include "Figure/AFigure.h"
#include "../Tools/Meta.h"

class ComplexPrimitive;
class PAlgorithm;
class PCycle;
class PFollow;
class PFork;
class PFunc;

class AScheduler
{
public:
    explicit AScheduler(const Meta &meta)
        : meta(meta)
    {}

    virtual ptrVector<AFigure> schedule(const std::unique_ptr<ComplexPrimitive> &algorithm) = 0;

    virtual bool schedulePrimitive(const PAlgorithm &primitive) = 0;
    virtual bool schedulePrimitive(const PCycle &primitive) = 0;
    virtual bool schedulePrimitive(const PFollow &primitive) = 0;
    virtual bool schedulePrimitive(const PFork &primitive) = 0;
    virtual bool schedulePrimitive(const PFunc &primitive) = 0;

protected:
    ptrVector<AFigure> figures;
    const Meta &meta;

protected:
    double getBotBorder()
    {
        return meta.ph() - meta.yp();
    }

    friend class FEmborderScheduler_pushContinueFigure_Test;
    friend class FEmborderScheduler_addForkTooTight_Test;
    friend class FEmborderScheduler_addForkBadWidth_Test;
    friend class FEmborderScheduler_addForkCommon_Test;
    friend class FEmborderScheduler_addFigureTooTight_Test;
    friend class FEmborderScheduler_addFigureBadWidth_Test;
    friend class FEmborderScheduler_addFigureCommon_Test;
    friend class FEmborderScheduler_connectForkPartsRightPageLess_Test;
    friend class FEmborderScheduler_connectForkPartsLeftPageLess_Test;
    friend class FEmborderScheduler_pushForkLines_Test;
    friend class FEmborderScheduler_pushSpaceLine_Test;
};

#endif //PARSER_SCHEDULER_ASCHEDULER_H_
