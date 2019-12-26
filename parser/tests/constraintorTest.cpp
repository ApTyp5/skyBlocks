#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by arthur on 05.12.2019.
//

#include <gtest/gtest.h>
#include "../Tools/Liner.h"
#include "../Fixtures/FIndentPythonLikeConstraintor.h"

TEST_F(FIndentPythonLikeConstraintor, findMainNoMain)
{
    std::wstring input = "def function (args)\n"
                         "  some func text\n"
                         "  some func text\n";
    size_t front;
    size_t back;

    EXPECT_EQ(false, constraintor->findMain(front, back, input));
    EXPECT_EQ(1, constraintor->errors.size());
}

TEST_F(FIndentPythonLikeConstraintor, findMainCommon)
{
    std::wstring input = "def function (args)\n"
                         "  some func text\n"
                         "  some func text\n"
                         "first wstring\n"
                         "second wstring\n"
                         "third wstring";
    size_t front;
    size_t back;
    EXPECT_EQ(true, constraintor->findMain(front, back, input));

    EXPECT_EQ(4, front);
    EXPECT_EQ(7, back);
}

int main(int argc, wchar_t *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop