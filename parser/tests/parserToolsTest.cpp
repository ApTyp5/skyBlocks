#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by arthur on 28.11.2019.
//

#include <gtest/gtest.h>

#include "../Tools/Liner.h"
#include "../Tools/SizedLiner.h"

TEST(sizedLiner, without_nl)
{
    size_t size = 5;
    std::string input = "first string\n" // 13 symbols
                        "second string\n" // 14 symbols
                        "third string\n"; // 13 symbols

    SizedLiner liner(input);
    std::vector<std::string> answers = {"first", " stri", "ng\n",
                                        "secon", "d str", "ing\n",
                                        "third", " stri", "ng\n"};
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
                        "third string\n"; // 13 symbols

    SizedLiner liner(input);
    std::vector<std::string> answers = {"firs\n", "t st\n", "ring\n",
                                        "seco\n", "nd s\n", "trin\n", "g\n",
                                        "thir\n", "d st\n", "ring\n",};
    std::string line;
    size_t c = 0;

    while (liner.getLine(line, size, true)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}

TEST(liner, without_nl)
{
    std::string input = "first string\n"
                        "second string\n"
                        "third string\n";
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
                        "third string\n";
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