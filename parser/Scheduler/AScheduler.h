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

    virtual bool schedulePrimitive(PAlgorithm &primitive, AScheduler &scheduler) = 0;
    virtual bool schedulePrimitive(PCycle &primitive, AScheduler &scheduler) = 0;
    virtual bool schedulePrimitive(PFollow &primitive, AScheduler &scheduler) = 0;
    virtual bool schedulePrimitive(PFork &primitive, AScheduler &scheduler) = 0;
    virtual bool schedulePrimitive(PFunc &primitive, AScheduler &scheduler) = 0;

protected:
    ptrVector<AFigure> figures;
    const Meta &meta;
};

#endif //PARSER_SCHEDULER_ASCHEDULER_H_
