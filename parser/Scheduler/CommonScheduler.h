//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_COMMONSCHEDULER_H_
#define PARSER_SCHEDULER_COMMONSCHEDULER_H_

#include "AScheduler.h"

class CommonScheduler: public AScheduler
{
public:
    CommonScheduler(const Meta &meta)
        : AScheduler(meta)
    {}
    ptrVector<AFigure> schedule(const std::unique_ptr<ComplexPrimitive> &algorithm) override;

    bool schedulePrimitive(PAlgorithm &primitive, AScheduler &scheduler) override;
    bool schedulePrimitive(PCycle &primitive, AScheduler &scheduler) override;
    bool schedulePrimitive(PFollow &primitive, AScheduler &scheduler) override;
    bool schedulePrimitive(PFork &primitive, AScheduler &scheduler) override;
    bool schedulePrimitive(PFunc &primitive, AScheduler &scheduler) override;
protected:

};

#endif //PARSER_SCHEDULER_COMMONSCHEDULER_H_
