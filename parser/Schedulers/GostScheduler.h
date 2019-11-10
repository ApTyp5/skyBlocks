//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_SCHEDULERS_GOSTSCHEDULER_H_
#define PARSER_SCHEDULERS_GOSTSCHEDULER_H_

#include "AbstractScheduler.h"

class GostScheduler: public AbstractScheduler {
 public:
  std::vector<AbstractFigure *> schedule(std::vector<AbstractPrimitive *>) override ;
};

#endif //PARSER_SCHEDULERS_GOSTSCHEDULER_H_
