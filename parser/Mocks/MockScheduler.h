//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_MOCKS_MOCKSCHEDULER_H_
#define PARSER_MOCKS_MOCKSCHEDULER_H_

#include <gmock/gmock.h>
#include "../Scheduler/AScheduler.h"

class MockScheduler: public AScheduler
{
public:
    MockScheduler(const Meta &meta)
        : AScheduler(meta)
    {}
    MOCK_METHOD(ptrVector<AFigure>, schedule, (const std::unique_ptr<ComplexPrimitive> &algorithm), (override));
    MOCK_METHOD(bool, schedulePrimitive, (const PAlgorithm &primitive), (override));
    MOCK_METHOD(bool, schedulePrimitive, (const PCycle &primitive), (override));
    MOCK_METHOD(bool, schedulePrimitive, (const PFollow &primitive), (override));
    MOCK_METHOD(bool, schedulePrimitive, (const PFork &primitive), (override));
    MOCK_METHOD(bool, schedulePrimitive, (const PFunc &primitive), (override));
};

#endif //PARSER_MOCKS_MOCKSCHEDULER_H_
