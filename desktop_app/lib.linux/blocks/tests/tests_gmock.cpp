#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Algorithm.h"
#include "Block.h"

using ::testing::AtLeast;
using ::testing::DoAll;
/*
class MockBlock : public Block {
public:
    MOCK_METHOD0(Draw, DrawData());
};

TEST(BlockTest, AlgorithmDrawTest) {
    MockBlock block;
    EXPECT_CALL(block, Draw()).Times(AtLeast(1));

    Algorithm algorithm;
    algorithm.Add(&block);
    algorithm.Draw();
}*/

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
