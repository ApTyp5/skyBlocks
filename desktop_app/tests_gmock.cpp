#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "blocks/Algorithm.h"
#include "blocks/Block.h"
#include "requests/ConcreteRequest.h"
#include "requests/Request.h"
#include "Connector.h"

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

TEST(ConnectorTest, SendRequestTest) {
    Request request;
    MockRequest mockRequest;
    EXPECT_CALL(mockRequest, GetRequestParams()).Times(AtLeast(1));

    request.SetRequest(&mockRequest);
    auto &connector = Connector::GetConnector();
    connector.SendRequest(&request);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
