#include "gmock/gmock.h"
#include "Mocks/MockParser.h"

TEST(parser, logical_test) {
  MockParser mock_parser;

}




int main(int argc, char *argv[]) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}