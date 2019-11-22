//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_ASCHEDULER_H_
#define PARSER_SCHEDULER_ASCHEDULER_H_

#include "Figure/AFigure.h"
#include "../Analyzer/Primitive/APrimitive.h"
#include "../ptrVector.h"

class AScheduler {
 public:
  virtual ptrVector<AFigure> &&schedule(const ptrVector<APrimitive> &primitives) = 0;
};

#endif //PARSER_SCHEDULER_ASCHEDULER_H_