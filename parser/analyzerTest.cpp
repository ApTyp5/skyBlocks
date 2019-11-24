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
#include "Analyzer/IndentAnalyze/Tools/Utils.h"

TEST(utils, is_in_vector_str_positive)
{
    std::vector<std::string> init = {"qwer", "asdf"};
    EXPECT_EQ(true, Utils::isInVector(std::string("qwer"), init));
    EXPECT_EQ(false, Utils::isInVector(std::string("zxcv"), init));
}

TEST(utils, is_in_vector_int_positive)
{
    std::vector<int> init = {1, 2, 3, 4, 5};
    for (int i = 1; i < 6; i++) {
        EXPECT_EQ(true, Utils::isInVector(i, init));
    }
    for (int i = 10; i < 12; i++) {
        EXPECT_EQ(false, Utils::isInVector(i, init));
    }
}

TEST(utils, str_append_mult_syms_positive)
{
    std::string init = "init";
    char suffix = '/';
    size_t num = 3;

    std::string output = Utils::strAppendMultipleSymbols(init, suffix, num);
    std::string exp_output = init + '/' + '/' + '/';
    EXPECT_STREQ(exp_output.data(), output.data());
}

TEST(utils, ret_first_word_negaitve)
{
    std::string test_string = "longword";
    std::string first = "longword";
    std::string others;
    std::string rec_first, rec_others;

    bool is_ok = Utils::extractFuncName(rec_first, rec_others, test_string);
    EXPECT_EQ(false, is_ok);
    EXPECT_STREQ(first.data(), rec_first.data());
    EXPECT_STREQ(others.data(), rec_others.data());
}

TEST(utils, ret_first_word_positive)
{
    std::string test_string = "first word";
    std::string first = "first";
    std::string others = "word";
    std::string rec_first, rec_others;

    bool is_ok = Utils::extractFuncName(rec_first, rec_others, test_string);
    EXPECT_EQ(true, is_ok);
    EXPECT_STREQ(first.data(), rec_first.data());
    EXPECT_STREQ(others.data(), rec_others.data());
}

TEST(utils, extract_func_name_positive)
{
    char delim = ' ';
    std::string test_string = "qwer asdf";
    std::string name = "qwer";
    std::string other = "asdf";
    std::string rec_name, rec_other;

    bool is_ok = Utils::extractFuncName(rec_name, rec_other, test_string, delim);
    EXPECT_EQ(true, is_ok);
    EXPECT_STREQ(name.data(), rec_name.data());
    EXPECT_STREQ(other.data(), rec_other.data());
}

TEST(utils, extract_func_name_negative)
{
    char delim = '/';
    std::string test_string = "qwer asdf";
    std::string name = "qwer asdf";
    std::string other;
    std::string rec_name, rec_other;

    bool is_ok = Utils::extractFuncName(rec_name, rec_other, test_string, delim);
    EXPECT_EQ(false, is_ok);
    EXPECT_STREQ(name.data(), rec_name.data());
    EXPECT_STREQ(other.data(), rec_other.data());
}

TEST(utils, cut_front_positive)
{
    std::string test_string("Useless textUsefull text");
    std::string ult("Useless text");
    std::string uft("Usefull text");

    std::string answer = Utils::cutFront(test_string, ult.size());
    EXPECT_STREQ(answer.data(), uft.data());
}

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

