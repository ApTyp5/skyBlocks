//
// Created by arthur on 24.11.2019.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>
#include "Analyzer/IndentAnalyze/Tools/Liner.h"

TEST(liner, common_work)
{
    std::string input = "qwer\n"
                        "asdf\n"
                        "zxcv\n";
    Liner liner(input);
    std::vector<std::string> answers = {"qwer\n", "asdf\n", "zxcv\n"};
    std::string line;
    size_t c = 0;

    while (liner.getLine(line)) {
        EXPECT_STREQ(answers[c].data(), line.data());
        c++;
    }

    EXPECT_EQ(answers.size(), c);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop

