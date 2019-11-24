//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_ASCHEDULER_H_
#define PARSER_SCHEDULER_ASCHEDULER_H_

#include "../Analyzer/Primitive/APrimitive.h"
#include "../ptrVector.h"
#include "Figure/AFigure.h"
#include "../Stubs/Stubs.h"

class AScheduler
{
public:
    virtual ptrVector<AFigure> schedule(const std::unique_ptr<ComplexPrimitive> &algorithm, Meta meta) = 0;
};

#endif //PARSER_SCHEDULER_ASCHEDULER_H_
