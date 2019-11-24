//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_COMMONSCHEDULER_H_
#define PARSER_SCHEDULER_COMMONSCHEDULER_H_

#include "AScheduler.h"

class CommonScheduler: public AScheduler
{
public:
    ptrVector<AFigure> schedule(const std::unique_ptr<ComplexPrimitive> &algorithm, Meta meta) override;
protected:
    void put(APrimitive *primitive, size_t curX, size_t curY, size_t maxY);
    void put(ComplexPrimitive *primitive, size_t curX, size_t curY, size_t maxY);
};

#endif //PARSER_SCHEDULER_COMMONSCHEDULER_H_
