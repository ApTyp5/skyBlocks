//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_SCHEDULERCREATOR_H_
#define PARSER_SCHEDULER_SCHEDULERCREATOR_H_

#include <memory>

#include "SchedulerType.h"
#include "AScheduler.h"
#include "CommonScheduler.h"

class SchedulerCreator {
 public:
  static AScheduler *create(SchedulerType type = Common) {
    switch (type) {
      default:
      case Common:return new CommonScheduler;
    }
  }
};
#endif //PARSER_SCHEDULER_SCHEDULERCREATOR_H_
