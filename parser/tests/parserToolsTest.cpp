#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by arthur on 28.11.2019.
//

#include <gtest/gtest.h>

#include "../Tools/Liner.h"
#include "../Tools/SizedLiner.h"


TEST(sizedLiner, endOfText)
{
    size_t size = 10;
    std::wstring input = "qwer";
    SizedLiner liner(input);

    EXPECT_EQ(false, liner.isEmpty());
    EXPECT_EQ(true, liner.getLine(input));
    EXPECT_EQ(true, liner.isEmpty());
}
TEST(sizedLiner, without_nl)
{
    size_t size = 5;
    std::wstring input = "first wstring\n" // 13 symbols
                         "second wstring\n" // 14 symbols
                         "third wstring"; // 13 symbols

    SizedLiner liner(input);
    std::vector<std::wstring> answers = {"first", " stri", "ng",
                                         "secon", "d str", "ing",
                                         "third", " stri", "ng"};
    std::wstring line;
    size_t c = 0;

    while (liner.getLine(line, size, false)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}
TEST(sizedLiner, with_nl)
{
    size_t size = 5;
    std::wstring input = "first wstring\n" // 13 symbols
                         "second wstring\n" // 14 symbols
                         "third wstring\n" // 13 symbols
                         "qwer qwert"; // 10 sym

    SizedLiner liner(input);
    std::vector<std::wstring> answers = {"first\n", " stri\n", "ng\n",
                                         "secon\n", "d str\n", "ing\n",
                                         "third\n", " stri\n", "ng\n",
                                         "qwer \n", "qwert\n"};
    std::wstring line;
    size_t c = 0;

    while (liner.getLine(line, size, true)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}
TEST(liner, endOfText)
{
    std::wstring input = "qwer";
    Liner liner(input);
    std::wstring line;

    EXPECT_EQ(false, liner.isEmpty());
    EXPECT_EQ(true, liner.getLine(line, false));
    EXPECT_EQ(true, liner.isEmpty());
}
TEST(liner, without_nl)
{
    std::wstring input = "first wstring\n"
                         "second wstring\n"
                         "third wstring";
    Liner liner(input);
    std::vector<std::wstring> answers = {"first wstring",
                                         "second wstring",
                                         "third wstring"};
    std::wstring line;
    size_t c = 0;

    while (liner.getLine(line, false)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}
TEST(liner, with_nl)
{
    std::wstring input = "first wstring\n"
                         "second wstring\n"
                         "third wstring";
    Liner liner(input);
    std::vector<std::wstring> answers = {"first wstring\n",
                                         "second wstring\n",
                                         "third wstring\n"};
    std::wstring line;
    size_t c = 0;

    while (liner.getLine(line, true)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}

int main(int argc, wchar_t *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


#pragma clang diagnostic pop