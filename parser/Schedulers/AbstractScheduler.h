//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_SCHEDULERS_ABSTRACTSCHEDULER_H_
#define PARSER_SCHEDULERS_ABSTRACTSCHEDULER_H_

#include "SchedulerType.h"
#include "../Primitives/AbstractPrimitive.h"
#include "../Figures/AbstractFigure.h"

class AbstractScheduler {
 public:
  virtual std::vector<AbstractFigure *> schedule(std::vector<AbstractPrimitive *>);
};

#endif //PARSER_SCHEDULERS_ABSTRACTSCHEDULER_H_
