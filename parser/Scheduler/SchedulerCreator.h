//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_SCHEDULERCREATOR_H_
#define PARSER_SCHEDULER_SCHEDULERCREATOR_H_

#include <memory>

#include "AScheduler.h"
#include "UniverseScheduler/EmborderScheduler.h"
#include "SchedulerType.h"
#include "../Stubs/Stubs.h"


class SchedulerCreator
{
public:
    static AScheduler *create(const Meta &meta, SchedulerType type = Universe)
    {
        switch (type) {
            default:
            case Universe:return new EmborderScheduler(meta);
        }
    }
};
#endif //PARSER_SCHEDULER_SCHEDULERCREATOR_H_
