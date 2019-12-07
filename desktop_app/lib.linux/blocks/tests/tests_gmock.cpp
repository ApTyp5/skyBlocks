#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Algorithm.h"
#include "Figure.h"
#include "FigureFactory.h"
#include "JsonObject.h"

using ::testing::AtLeast;
using ::testing::DoAll;

class MockBlock : public Figure {
public:
    MOCK_METHOD0(Draw, DrawData*());
};

TEST(BlockTest, AlgorithmDrawTest) {
    auto figure = new MockBlock;
    EXPECT_CALL(*figure, Draw()).Times(AtLeast(1));

    Algorithm algorithm;
    algorithm.Add(figure);
    algorithm.DrawAll();
}

class MockJson : public JsonObject {
public:
    MockJson() = default;

    bool CheckCorrect() const override { return true; }
    bool IsArray() const override { return false; }
    int Count() const override { return 0; }

    FigureData * GetFigure(int num) const override { return nullptr; }


    MOCK_METHOD0(CheckCorrect, bool());
    MOCK_METHOD0(IsArray, bool());
    MOCK_METHOD0(Count, int());
    MOCK_METHOD1(GetFigure, FigureData*(int num));
};

TEST(JsonObject, FigureFactoryCreateNull) {
    MockJson json;

    EXPECT_CALL(json, CheckCorrect()).Times(AtLeast(1));
    EXPECT_CALL(json, IsArray()).Times(AtLeast(1));

    FigureFactory factory;
    factory.CreateAlgorithm(json);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
