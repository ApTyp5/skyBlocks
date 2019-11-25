//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_SCHEDULERCREATOR_H_
#define PARSER_SCHEDULER_SCHEDULERCREATOR_H_

#include <memory>

#include "AScheduler.h"
#include "CommonScheduler.h"
#include "SchedulerType.h"
#include "../Stubs/Stubs.h"


class SchedulerCreator
{
public:
    static AScheduler *create(const Meta &meta, SchedulerType type = Common)
    {
        switch (type) {
            default:
            case Common:return new CommonScheduler(meta);
        }
    }
};
#endif //PARSER_SCHEDULER_SCHEDULERCREATOR_H_
