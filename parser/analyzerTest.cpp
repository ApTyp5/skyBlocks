//
// Created by arthur on 24.11.2019.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>
#include "Analyzer/IndentAnalyze/Tools/Liner.h"
#include "Analyzer/IndentAnalyze/Tools/Memory.h"
#include "Analyzer/Primitive/PAlgorithm.h"
#include "Analyzer/Primitive/PFork.h"


TEST(memory, merge_positive)
{
    auto memory = new Memory(Alg, new PAlgorithm("name", "text"));
    auto merged_memory = new Memory(Fork, new PFork("text"));

    EXPECT_EQ(0, memory->getComplexPrimitive()->childrenNum());
    memory->merge(merged_memory);
    EXPECT_EQ(1, memory->getComplexPrimitive()->childrenNum());
    EXPECT_EQ(nullptr, merged_memory);
    delete memory;
}

TEST(liner, positive)
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

