//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_SCHEDULERS_ABSTRACTSCHEDULER_H_
#define PARSER_SCHEDULERS_ABSTRACTSCHEDULER_H_

#include "SchedulerType.h"
#include "../Primitives/AbstractPrimitive.h"
#include "../Figures/AbstractFigure.h"
#include "../Analyzers/BaseAnalyzer.h"

#include <memory>
#include <vector>

typedef std::vector<std::shared_ptr<AbstractFigure> > Figures;

class AbstractScheduler {
 public:
  virtual Figures schedule(Primitives) = 0;
};

#endif //PARSER_SCHEDULERS_ABSTRACTSCHEDULER_H_
