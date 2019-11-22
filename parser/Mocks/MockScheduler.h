//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_MOCKS_MOCKSCHEDULER_H_
#define PARSER_MOCKS_MOCKSCHEDULER_H_

#include <gmock/gmock.h>
#include "../Scheduler/AScheduler.h"

class MockScheduler : public AScheduler {
 public:
  MOCK_METHOD(ptrVector<AFigure> &&, schedule, (const ptrVector<APrimitive> &primitives), (override));
};

#endif //PARSER_MOCKS_MOCKSCHEDULER_H_
