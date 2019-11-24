//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_ASCHEDULER_H_
#define PARSER_SCHEDULER_ASCHEDULER_H_

#include "../Analyzer/Primitive/APrimitive.h"
#include "../ptrVector.h"
#include "Figure/AFigure.h"

class AScheduler
{
public:
    virtual ptrVector<AFigure> schedule(const std::unique_ptr<ComplexPrimitive> &algorithm) = 0;
};

#endif //PARSER_SCHEDULER_ASCHEDULER_H_
