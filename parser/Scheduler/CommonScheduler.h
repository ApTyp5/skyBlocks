//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_COMMONSCHEDULER_H_
#define PARSER_SCHEDULER_COMMONSCHEDULER_H_

#include "AScheduler.h"

class CommonScheduler: public AScheduler
{
public:
    ptrVector<AFigure> schedule(const std::unique_ptr<ComplexPrimitive> &algorithm) override;
};

#endif //PARSER_SCHEDULER_COMMONSCHEDULER_H_
