//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_SCHEDULERCREATOR_H_
#define PARSER_SCHEDULER_SCHEDULERCREATOR_H_

#include <memory>

#include "AScheduler.h"
#include "SchedulerType.h"
#include "EmborderScheduler/GostScheduler.h"

class SchedulerCreator
{
public:
    static AScheduler *create(const Meta &meta, SchedulerType type = Embordered)
    {
        switch (type) {
            default:
            case Embordered:return new GostScheduler(meta);
        }
    }
};

#endif //PARSER_SCHEDULER_SCHEDULERCREATOR_H_
