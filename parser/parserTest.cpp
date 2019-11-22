#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>

#include "Parser.h"
#include "Mocks/MockScheduler.h"
#include "Mocks/MockAnalyzeFactory.h"
#include "Mocks/MockParser.h"

#include "Analyzer/AnalyzeFactoryCreator.h"

#include "Scheduler/SchedulerCreator.h"

TEST(parser, mock) {
  MockParser parser;
  auto *mock_analyze_factory = new MockAnalyzeFactory;
  auto *scheduler = new MockScheduler;

  EXPECT_CALL(*mock_analyze_factory, createConstraintor).Times(1);
  EXPECT_CALL(*mock_analyze_factory, createAnalyzer).Times(1);
  EXPECT_CALL(*scheduler, schedule).Times(1);
  EXPECT_CALL(parser, formJson).Times(1);

  parser.parse("doesn't matter", Meta(), mock_analyze_factory, scheduler);

  delete mock_analyze_factory;
  delete scheduler;
}

/*TEST(parser, parse_follow){
  std::string input = "begin\n\n"
                      "follow1\nfollow2\n\n"
                      "end\n\n";
  Parser parser;
  std::unique_ptr<AAnalyzeFactory> analyze_factory(AnalyzeFactoryCreator::create(Indent));
  std::unique_ptr<AScheduler> scheduler(SchedulerCreator::create(Common));

  std::string output = parser.parse(input, Meta(), analyze_factory.get(), scheduler.get());

  std::string expected = "qwer";
}

TEST(parser, parse_while){
  std::string input = "begin\n\n"
                      "while\nfollow2\n\n"
                      "end\n\n";
  Parser parser;
  std::unique_ptr<AAnalyzeFactory> analyze_factory(AnalyzeFactoryCreator::create(Indent));
  std::unique_ptr<AScheduler> scheduler(SchedulerCreator::create(Common));

  std::string output = parser.parse(input, Meta(), analyze_factory.get(), scheduler.get());
  std::string expected = "qwer";
}*/

int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
#pragma clang diagnostic pop