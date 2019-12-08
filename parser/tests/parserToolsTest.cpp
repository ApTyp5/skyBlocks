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
    std::string input = "qwer";
    SizedLiner liner(input);

    EXPECT_EQ(false, liner.isEmpty());
    EXPECT_EQ(true, liner.getLine(input));
    EXPECT_EQ(true, liner.isEmpty());
}
TEST(sizedLiner, without_nl)
{
    size_t size = 5;
    std::string input = "first string\n" // 13 symbols
                        "second string\n" // 14 symbols
                        "third string"; // 13 symbols

    SizedLiner liner(input);
    std::vector<std::string> answers = {"first", " stri", "ng",
                                        "secon", "d str", "ing",
                                        "third", " stri", "ng"};
    std::string line;
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
    std::string input = "first string\n" // 13 symbols
                        "second string\n" // 14 symbols
                        "third string\n" // 13 symbols
                        "qwer qwert"; // 10 sym

    SizedLiner liner(input);
    std::vector<std::string> answers = {"first\n", " stri\n", "ng\n",
                                        "secon\n", "d str\n", "ing\n",
                                        "third\n", " stri\n", "ng\n",
                                        "qwer \n", "qwert\n"};
    std::string line;
    size_t c = 0;

    while (liner.getLine(line, size, true)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}
TEST(liner, endOfText)
{
    std::string input = "qwer";
    Liner liner(input);
    std::string line;

    EXPECT_EQ(false, liner.isEmpty());
    EXPECT_EQ(true, liner.getLine(line, false));
    EXPECT_EQ(true, liner.isEmpty());
}
TEST(liner, without_nl)
{
    std::string input = "first string\n"
                        "second string\n"
                        "third string";
    Liner liner(input);
    std::vector<std::string> answers = {"first string",
                                        "second string",
                                        "third string"};
    std::string line;
    size_t c = 0;

    while (liner.getLine(line, false)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}
TEST(liner, with_nl)
{
    std::string input = "first string\n"
                        "second string\n"
                        "third string";
    Liner liner(input);
    std::vector<std::string> answers = {"first string\n",
                                        "second string\n",
                                        "third string\n"};
    std::string line;
    size_t c = 0;

    while (liner.getLine(line, true)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


#pragma clang diagnostic pop