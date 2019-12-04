#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "blocks/Algorithm.h"
#include "blocks/Block.h"

using ::testing::AtLeast;
using ::testing::DoAll;

class MockBlock : public Block {
public:
    MOCK_METHOD0(Draw, void());
};

TEST(BlockTest, AlgorithmDrawTest) {
    MockBlock block;
    EXPECT_CALL(block, Draw()).Times(AtLeast(1));

    Algorithm algorithm;
    algorithm.Add(&block);
    algorithm.Draw();
}

class MockRequest : public ConcreteRequest {
public:
    MOCK_METHOD0(GetRequestParams, void());
};