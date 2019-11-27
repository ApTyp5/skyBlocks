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

#include "../ptrVector.h"
#include "Figure/AFigure.h"
#include "../Stubs/Stubs.h"

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

    virtual bool schedulePrimitive(const PAlgorithm &primitive, AScheduler &scheduler) = 0;
    virtual bool schedulePrimitive(const PCycle &primitive, AScheduler &scheduler) = 0;
    virtual bool schedulePrimitive(const PFollow &primitive, AScheduler &scheduler) = 0;
    virtual bool schedulePrimitive(const PFork &primitive, AScheduler &scheduler) = 0;
    virtual bool schedulePrimitive(const PFunc &primitive, AScheduler &scheduler) = 0;

protected:
    ptrVector<AFigure> figures;
    const Meta &meta;

protected:
    virtual size_t BlockWidth(const std::string &text)
    {
        return meta.symbolWidth() * (meta.xPadding() + text.size());
    }

    virtual size_t BlockHeight(size_t lineNum)
    {
        return meta.lineHeight() * (meta.yPadding() + lineNum);
    }

    size_t getBotBorder()
    {
        return meta.pageHeight() - meta.yMargin();
    }

    size_t getLeftBorder()
    {
        return meta.xMargin();
    }

    size_t getRightBorder()
    {
        return meta.pageWidth() - meta.xMargin();
    }
};

#endif //PARSER_SCHEDULER_ASCHEDULER_H_
