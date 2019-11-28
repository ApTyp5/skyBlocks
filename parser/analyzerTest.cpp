//
// Created by arthur on 24.11.2019.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>
#include "Tools/Liner.h"
#include "Analyzer/IndentAnalyze/Tools/Memory.h"
#include "Analyzer/Primitive/PAlgorithm.h"
#include "Analyzer/Primitive/PFork.h"
#include "Analyzer/IndentAnalyze/Tools/IndentAnalyzerUtils.h"
#include "Fixtures/FixtureIndentAnalyzer.h"

TEST(IndentAnalyzer, analyze_if)
{
    ptrVector<Error> errors;
    auto *analyzer = new IndentAnalyzer(errors);
    std::string text = "begin\n"
                       "if true\n"
                       "    smth\n"
                       "else\n"
                       "    smth2\n"
                       "end\n";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 0));
    EXPECT_EQ(3, prim_ptr->childrenNum());
    EXPECT_EQ("begin\n", prim_ptr->getChildern()[0]->getInnerText());
    EXPECT_EQ("true\n", prim_ptr->getChildern()[1]->getInnerText());
    EXPECT_EQ("end\n", prim_ptr->getChildern()[2]->getInnerText());

    EXPECT_EQ(false, prim_ptr->getChildern()[0]->hasChildren());
    EXPECT_EQ(true, prim_ptr->getChildern()[1]->hasChildren());
    EXPECT_EQ(false, prim_ptr->getChildern()[0]->hasChildren());

    auto iff = dynamic_cast<const ComplexPrimitive *>(prim_ptr->getChildern()[1]);

    EXPECT_EQ(1, iff->childrenNum());
    EXPECT_EQ("smth\n", iff->getChildern()[0]->getInnerText());
//    EXPECT_EQ("smth2\n", iff->getChildern()[1]->getInnerText());

    EXPECT_EQ(false, iff->getChildern()[0]->hasChildren());
//    EXPECT_EQ(false, iff->getChildern()[1]->hasChildren());
}

TEST(IndentAnalyzer, analyze_cycle)
{
    ptrVector<Error> errors;
    auto *analyzer = new IndentAnalyzer(errors);
    std::string text = "begin\n"
                       "while true\n"
                       "    smth\n"
                       "\n"
                       "    smth2\n"
                       "end\n";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 0));
    EXPECT_EQ(3, prim_ptr->childrenNum());
    EXPECT_EQ("begin\n", prim_ptr->getChildern()[0]->getInnerText());
    EXPECT_EQ("true\n", prim_ptr->getChildern()[1]->getInnerText());
    EXPECT_EQ("end\n", prim_ptr->getChildern()[2]->getInnerText());

    EXPECT_EQ(false, prim_ptr->getChildern()[0]->hasChildren());
    EXPECT_EQ(true, prim_ptr->getChildern()[1]->hasChildren());
    EXPECT_EQ(false, prim_ptr->getChildern()[0]->hasChildren());

    auto whil = dynamic_cast<const ComplexPrimitive *>(prim_ptr->getChildern()[1]);

    EXPECT_EQ(2, whil->childrenNum());
    EXPECT_EQ("smth\n", whil->getChildern()[0]->getInnerText());
    EXPECT_EQ("smth2\n", whil->getChildern()[1]->getInnerText());

    EXPECT_EQ(false, whil->getChildern()[0]->hasChildren());
    EXPECT_EQ(false, whil->getChildern()[1]->hasChildren());
}

TEST(IndentAnalyzer, analyze_2_follow)
{
    ptrVector<Error> errors;
    auto *analyzer = new IndentAnalyzer(errors);

    std::string text = "begin\n"
                       "\n"
                       "end\n";

    ComplexPrimitive *prim_ptr(analyzer->analyze(text, 0));
    EXPECT_EQ(2, prim_ptr->childrenNum());
    EXPECT_EQ("begin\n", prim_ptr->getChildern()[0]->getInnerText());
    EXPECT_EQ("end\n", prim_ptr->getChildern()[1]->getInnerText());
    delete (prim_ptr);
}

TEST_F(FixtureIndentAnalyzer, try_add_pfollow_positive)
{
    analyzer->shortMemory = "qwer";
    EXPECT_EQ(0, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
    analyzer->tryAddPFollowToLastMem();
    EXPECT_EQ(1, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
    EXPECT_EQ(true, analyzer->shortMemory.empty());
}

TEST_F(FixtureIndentAnalyzer, merge_back_mem)
{
    analyzer->longMemory.push_back(new Memory(Fork, new PFork("text")));
    EXPECT_EQ(2, analyzer->longMemory.size());
    analyzer->mergeBackMemory();
    EXPECT_EQ(1, analyzer->longMemory.size());
    EXPECT_EQ(1, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
}

TEST_F(FixtureIndentAnalyzer, ret_indent)
{
    std::string str = "\t\t\tqwer";
    std::string indent = analyzer->retIndent(str);
    EXPECT_STREQ("\t\t\t", indent.data());
}

TEST_F(FixtureIndentAnalyzer, get_current_indent)
{
    analyzer->indent = "qwer";
    analyzer->state_ = Cycle;
    EXPECT_STREQ("qwer", analyzer->getCurrentIndent().data());

    analyzer->state_ = Fork;
    EXPECT_STREQ("qwer", analyzer->getCurrentIndent().data());

    analyzer->state_ = Follow;
    analyzer->longMemory.back()->setBodyIndent("asdf");
    EXPECT_STREQ("asdf", analyzer->getCurrentIndent().data());
}

TEST(analyzer_utils, is_in_vector_str_positive)
{
    std::vector<std::string> init = {"qwer", "asdf"};
    EXPECT_EQ(true, IndentAnalyzerUtils::isInVector(std::string("qwer"), init));
    EXPECT_EQ(false, IndentAnalyzerUtils::isInVector(std::string("zxcv"), init));
}

TEST(analyzer_utils, is_in_vector_int_positive)
{
    std::vector<int> init = {1, 2, 3, 4, 5};
    for (int i = 1; i < 6; i++) {
        EXPECT_EQ(true, IndentAnalyzerUtils::isInVector(i, init));
    }
    for (int i = 10; i < 12; i++) {
        EXPECT_EQ(false, IndentAnalyzerUtils::isInVector(i, init));
    }
}

TEST(analyzer_utils, str_append_mult_syms_positive)
{
    std::string init = "init";
    char suffix = '/';
    size_t num = 3;

    std::string output = IndentAnalyzerUtils::strAppendMultipleSymbols(init, suffix, num);
    std::string exp_output = init + '/' + '/' + '/';
    EXPECT_STREQ(exp_output.data(), output.data());
}

TEST(analyzer_utils, ret_first_word_negaitve)
{
    std::string test_string = "longword";
    std::string first = "longword";
    std::string others;
    std::string rec_first, rec_others;

    bool is_ok = IndentAnalyzerUtils::extractFuncName(rec_first, rec_others, test_string);
    EXPECT_EQ(false, is_ok);
    EXPECT_STREQ(first.data(), rec_first.data());
    EXPECT_STREQ(others.data(), rec_others.data());
}

TEST(analyzer_utils, ret_first_word_positive)
{
    std::string test_string = "first word";
    std::string first = "first";
    std::string others = "word";
    std::string rec_first, rec_others;

    bool is_ok = IndentAnalyzerUtils::extractFuncName(rec_first, rec_others, test_string);
    EXPECT_EQ(true, is_ok);
    EXPECT_STREQ(first.data(), rec_first.data());
    EXPECT_STREQ(others.data(), rec_others.data());
}

TEST(analyzer_utils, extract_func_name_positive)
{
    char delim = ' ';
    std::string test_string = "qwer asdf";
    std::string name = "qwer";
    std::string other = "asdf";
    std::string rec_name, rec_other;

    bool is_ok = IndentAnalyzerUtils::extractFuncName(rec_name, rec_other, test_string, delim);
    EXPECT_EQ(true, is_ok);
    EXPECT_STREQ(name.data(), rec_name.data());
    EXPECT_STREQ(other.data(), rec_other.data());
}

TEST(analyzer_utils, extract_func_name_negative)
{
    char delim = '/';
    std::string test_string = "qwer asdf";
    std::string name = "qwer asdf";
    std::string other;
    std::string rec_name, rec_other;

    bool is_ok = IndentAnalyzerUtils::extractFuncName(rec_name, rec_other, test_string, delim);
    EXPECT_EQ(false, is_ok);
    EXPECT_STREQ(name.data(), rec_name.data());
    EXPECT_STREQ(other.data(), rec_other.data());
}

TEST(analyzer_utils, cut_front_positive)
{
    std::string test_string("Useless textUsefull text");
    std::string ult("Useless text");
    std::string uft("Usefull text");

    std::string answer = IndentAnalyzerUtils::cutFront(test_string, ult.size());
    EXPECT_STREQ(answer.data(), uft.data());
}

TEST(analyzer_utils, skip_symbols)
{
    std::string str(" \t qwer");
    std::vector<char> syms = {' ', '\t'};

    EXPECT_STREQ("qwer", IndentAnalyzerUtils::skipSymbols(str, syms).data());
}

TEST(memory, merge_positive)
{
    auto memory = new Memory(Alg, new PAlgorithm("text"));
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

