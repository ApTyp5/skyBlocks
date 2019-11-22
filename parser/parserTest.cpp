#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>

#include "Parser.h"
#include "Mocks/MockScheduler.h"
#include "Mocks/MockAnalyzeFactory.h"

TEST(parser, mock_test) {
  Parser parser;
  auto *mock_analyze_factory = new MockAnalyzeFactory;
  auto *scheduler = new MockScheduler;

  EXPECT_CALL(*mock_analyze_factory, createConstraintor).Times(1);
  EXPECT_CALL(*mock_analyze_factory, createAnalyzer).Times(1);
  EXPECT_CALL(*scheduler, schedule).Times(1);

  parser.parse("doesn't matter", Meta(), mock_analyze_factory, scheduler);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
#pragma clang diagnostic pop