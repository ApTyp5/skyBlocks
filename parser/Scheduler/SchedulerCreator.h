//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_SCHEDULERCREATOR_H_
#define PARSER_SCHEDULER_SCHEDULERCREATOR_H_

#include <memory>

#include "SchedulerType.h"

class SchedulerCreator {
 public:
  static std::unique_ptr<AScheduler> &UPtrCreate(SchedulerType type) {
    switch (type) {
      case SchedulerType::CommonScheduler:return std::unique_ptr<AScheduler>(new CommonScheduler);
    }
  }
};
#endif //PARSER_SCHEDULER_SCHEDULERCREATOR_H_
