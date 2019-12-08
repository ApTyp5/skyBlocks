#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>

#include "../Parser.h"
#include "../Mocks/MockScheduler.h"
#include "../Mocks/MockAnalyzeFactory.h"
#include "../Mocks/MockParser.h"

#include "../Analyzer/AnalyzeFactoryCreator.h"

#include "../Scheduler/SchedulerCreator.h"

/*TEST(parser, mock)
{
    Meta meta;
    MockParser parser;
    auto *mock_analyze_factory = new MockAnalyzeFactory;
    auto *scheduler = new MockScheduler(meta);

    EXPECT_CALL(*mock_analyze_factory, createConstraintor(parser.errors)).Times(1);
    EXPECT_CALL(*mock_analyze_factory, createAnalyzer(parser.errors)).Times(1);
    EXPECT_CALL(*scheduler, schedule).Times(1);

    parser.parse("doesn't matter", mock_analyze_factory, scheduler);

    delete mock_analyze_factory;
    delete scheduler;
}*/

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop