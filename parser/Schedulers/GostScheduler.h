//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_SCHEDULERS_GOSTSCHEDULER_H_
#define PARSER_SCHEDULERS_GOSTSCHEDULER_H_

#include "AbstractScheduler.h"

class GostScheduler: public AbstractScheduler {
 public:
  Figures schedule(Primitives primitives) override;
};

#endif //PARSER_SCHEDULERS_GOSTSCHEDULER_H_
