//
// Created by arthur on 15.11.2019.
//

#ifndef PARSER_MOCKS_MOCKSCHEDULER_H_
#define PARSER_MOCKS_MOCKSCHEDULER_H_

#include "../Schedulers/AbstractScheduler.h"
#include "gmock/gmock.h"

class MockSheduler : public AbstractScheduler {
 public:
  MOCK_METHOD(Figures, schedule, (Primitives), (override));
};

#endif //PARSER_MOCKS_MOCKSCHEDULER_H_
