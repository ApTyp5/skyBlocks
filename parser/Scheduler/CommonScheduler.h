//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_COMMONSCHEDULER_H_
#define PARSER_SCHEDULER_COMMONSCHEDULER_H_

#include "AScheduler.h"

class CommonScheduler: public AScheduler
{
public:
    ptrVector<AFigure> schedule(const ptrVector<APrimitive> &primitives) override;
};

#endif //PARSER_SCHEDULER_COMMONSCHEDULER_H_
