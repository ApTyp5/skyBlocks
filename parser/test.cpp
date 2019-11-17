#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "gmock/gmock.h"

#include "Mocks/MockAnalyzer.h"
#include "Mocks/MockScheduler.h"
#include "Parser.h"

TEST(first_working, mock_test) {
  Parser parser;
  std::shared_ptr<MockAnalyzer> analyzer(new MockAnalyzer);
  std::shared_ptr<MockSheduler> scheduler(new MockSheduler);

  EXPECT_CALL(*analyzer, analyze).Times(1);
  EXPECT_CALL(*scheduler, schedule).Times(1);

  parser.parse("some string", analyzer, scheduler);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
#pragma clang diagnostic pop