//
// Created by arthur on 24.11.2019.
//

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <gmock/gmock.h>
#include "../Tools/Liner.h"
#include "../Analyzer/IndentAnalyze/Tools/Memory.h"
#include "../Analyzer/Primitive/PAlgorithm.h"
#include "../Analyzer/Primitive/PFork.h"
#include "../Analyzer/IndentAnalyze/Tools/IndentAnalyzerUtils.h"
#include "../Fixtures/FIndentPythonLikeAnalyzer.h"

TEST(IndentAnalyzer, great_test)
{
    ptrVector<ParseError> errors;
    auto *analyzer = new IndentAnalyzer(errors, new PythonLikeAlphabet);
    std::string text = "some text, some text\n"
                       "moooore text\n"
                       "\n"
                       "ano block\n"
                       "of\n"
                       "text\n"
                       "\n"
                       "if some condition\n"
                       "   it is multiline condition\n"
                       "\tdo smth useless\n"
                       "else\n"
                       "   while top text;   \tbot text\n"
                       "\t\tinner block\n"
                       "   after while block\n"
                       "after if block\n"
                       "\n"
                       "bye-bye block";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 1, 18));
    EXPECT_EQ(5, prim_ptr->childrenNum());
    auto *f1 = prim_ptr->getChildren()[0];
    auto *f2 = prim_ptr->getChildren()[1];
    auto if1 = dynamic_cast<const PFork *>(prim_ptr->getChildren()[2]);
    auto *f3 = prim_ptr->getChildren()[3];
    auto *f4 = prim_ptr->getChildren()[4];

    EXPECT_STREQ("some text, some text\nmoooore text", f1->getInnerText().data());
    EXPECT_STREQ("ano block\nof\ntext", f2->getInnerText().data());
    EXPECT_STREQ("some condition\nit is multiline condition", if1->getInnerText().data());
    EXPECT_STREQ("after if block", f3->getInnerText().data());
    EXPECT_STREQ("bye-bye block", f4->getInnerText().data());

    EXPECT_EQ(1, if1->getChildren().size());
    EXPECT_EQ(2, if1->getElseChildren().size());

    EXPECT_STREQ("do smth useless", if1->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ("after while block", if1->getElseChildren()[1]->getInnerText().data());

    auto *w = dynamic_cast<const PCycle *>(if1->getElseChildren()[0]);
    EXPECT_STREQ("top text", w->getBeforeCycyleText().data());
    EXPECT_STREQ("bot text", w->getAfterCycleText().data());
    EXPECT_EQ(1, w->getChildren().size());
    EXPECT_STREQ("inner block", w->getChildren()[0]->getInnerText().data());
}

TEST(IndentAnalyzer, funcTest)
{
    ptrVector<ParseError> errors;
    auto *analyzer = new IndentAnalyzer(errors, new PythonLikeAlphabet);
    std::string text = "begin\n"
                       "call funcname (some args)\n"
                       "end";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 1, 9));
    EXPECT_EQ(3, prim_ptr->childrenNum());

    auto func = dynamic_cast<const PFunc *>(prim_ptr->getChildren()[1]);
    EXPECT_STREQ("funcname", func->getName().data());
    EXPECT_STREQ("(some args)", func->getInnerText().data());
}
TEST(IndentAnalyzer, analyze_if)
{
    ptrVector<ParseError> errors;
    auto *analyzer = new IndentAnalyzer(errors, new PythonLikeAlphabet);
    std::string text = "begin\n"
                       "if\tcond\n"
                       "  \tcontinue cond\n"
                       "\n"
                       "    smth\n"
                       "else\n"
                       "    smth2\n"
                       "end";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 1, 9));
    EXPECT_EQ(3, prim_ptr->childrenNum());
    EXPECT_STREQ("begin", prim_ptr->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ("cond\ncontinue cond", prim_ptr->getChildren()[1]->getInnerText().data());
    EXPECT_STREQ("end", prim_ptr->getChildren()[2]->getInnerText().data());

    EXPECT_EQ(false, prim_ptr->getChildren()[0]->hasChildren());
    EXPECT_EQ(true, prim_ptr->getChildren()[1]->hasChildren());
    EXPECT_EQ(false, prim_ptr->getChildren()[0]->hasChildren());

    auto iff = dynamic_cast<const PFork *>(prim_ptr->getChildren()[1]);

    EXPECT_EQ(1, iff->childrenNum());
    EXPECT_STREQ("smth", iff->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ("smth2", iff->getElseChildren()[0]->getInnerText().data());

    EXPECT_EQ(false, iff->getChildren()[0]->hasChildren());
    EXPECT_EQ(false, iff->getElseChildren()[0]->hasChildren());
}
TEST(IndentAnalyzer, analyze_cycle)
{
    ptrVector<ParseError> errors;
    auto *analyzer = new IndentAnalyzer(errors, new PythonLikeAlphabet);
    std::string text = "begin\n"
                       "while top word; botword\n"
                       "      more bot words\n"
                       "    smth\n"
                       "\n"
                       "    smth2\n"
                       "end\n";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 1, 8));
    EXPECT_EQ(3, prim_ptr->childrenNum());
    EXPECT_STREQ("begin", prim_ptr->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ("top word", prim_ptr->getChildren()[1]->getInnerText().data());
    EXPECT_STREQ("end", prim_ptr->getChildren()[2]->getInnerText().data());

    EXPECT_EQ(false, prim_ptr->getChildren()[0]->hasChildren());
    EXPECT_EQ(true, prim_ptr->getChildren()[1]->hasChildren());
    EXPECT_EQ(false, prim_ptr->getChildren()[0]->hasChildren());

    auto whil = dynamic_cast<const PCycle *>(prim_ptr->getChildren()[1]);

    EXPECT_EQ(2, whil->childrenNum());
    EXPECT_STREQ("botword\nmore bot words", whil->getAfterCycleText().data());
    EXPECT_STREQ("top word", whil->getBeforeCycyleText().data());
    EXPECT_STREQ("smth", whil->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ("smth2", whil->getChildren()[1]->getInnerText().data());

    EXPECT_EQ(false, whil->getChildren()[0]->hasChildren());
    EXPECT_EQ(false, whil->getChildren()[1]->hasChildren());

    delete analyzer;
}
TEST_F(FIndentPythonLikeAnalyzer, analyze_2_follow)
{
    std::string text = "begin\n"
                       "\n"
                       "end\n";

    ComplexPrimitive *prim_ptr(analyzer->analyze(text, 1, 4));
    EXPECT_EQ(2, prim_ptr->childrenNum());
    EXPECT_EQ("begin", prim_ptr->getChildren()[0]->getInnerText());
    EXPECT_EQ("end", prim_ptr->getChildren()[1]->getInnerText());
}
TEST_F(FIndentPythonLikeAnalyzer, try_add_pfollow_positive)
{
    analyzer->longMemory.push_back(new Memory(State::Alg, new PAlgorithm("")));
    analyzer->shortMemory = "qwer";
    EXPECT_EQ(0, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
    analyzer->tryAddPFollowToLastMem();
    EXPECT_EQ(1, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
    EXPECT_EQ(true, analyzer->shortMemory.empty());
}
TEST_F(FIndentPythonLikeAnalyzer, merge_back_mem)
{
    analyzer->longMemory.push_back(new Memory(State::Alg, new PAlgorithm("")));
    analyzer->longMemory.push_back(new Memory(State::Fork, new PFork("text")));
    EXPECT_EQ(2, analyzer->longMemory.size());
    analyzer->mergeBackMemory();
    EXPECT_EQ(1, analyzer->longMemory.size());
    EXPECT_EQ(1, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
}
TEST_F(FIndentPythonLikeAnalyzer, ret_indent)
{
    std::string str = "\t\t\tqwer";
    std::string indent = analyzer->retIndent(str);
    EXPECT_STREQ("\t\t\t", indent.data());
}
TEST_F(FIndentPythonLikeAnalyzer, get_current_indent)
{
    analyzer->longMemory.push_back(new Memory(State::Alg, new PAlgorithm("__main__")));
    analyzer->indent = "qwer";
    analyzer->state_ = State::Cycle;
    EXPECT_STREQ("qwer", analyzer->getCurrentIndent().data());

    analyzer->state_ = State::Fork;
    EXPECT_STREQ("qwer", analyzer->getCurrentIndent().data());

    analyzer->state_ = State::Follow;
    analyzer->longMemory.back()->setBodyIndent("asdf");
    EXPECT_STREQ("asdf", analyzer->getCurrentIndent().data());
}
TEST_F(FIndentPythonLikeAnalyzer, is_def_positive)
{
    std::string input = "def name (args)";
    EXPECT_EQ(true, analyzer->isDef(input));
}
TEST_F(FIndentPythonLikeAnalyzer, is_def_negative)
{
    std::string input = "notdef name (args)";
    EXPECT_EQ(false, analyzer->isDef(input));
}
TEST_F(FIndentPythonLikeAnalyzer, is_def_negative2)
{
    std::string input = " def name (args)";
    EXPECT_EQ(false, analyzer->isDef(input));
}
TEST(analyzer_utils, extract_second_word_positive2)
{
    std::vector<char> delims = {' ', '\t'};
    std::string str = "qwer asdf zxcv";
    std::string sWord;
    EXPECT_EQ(true, IndentAnalyzerUtils::extractSecondWord(sWord, str, delims));
    EXPECT_STREQ("asdf", sWord.data());
}
TEST(analyzer_utils, extract_second_word_positive)
{
    std::vector<char> delims = {' ', '\t'};
    std::string str = "qwer asdf";
    std::string sWord;
    EXPECT_EQ(true, IndentAnalyzerUtils::extractSecondWord(sWord, str, delims));
    EXPECT_STREQ("asdf", sWord.data());
}
TEST(analyzer_utils, extract_second_word_negative)
{
    std::vector<char> delims = {' ', '\t'};
    std::string str = "qwer";
    std::string sWord;
    EXPECT_EQ(false, IndentAnalyzerUtils::extractSecondWord(sWord, str, delims));
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
TEST(analyzer_utils, delim_string_negaitve)
{
    std::string test_string = "longword";
    std::string first = "longword";
    std::string others;
    std::string rec_first, rec_others;

    bool is_ok = IndentAnalyzerUtils::delimString(rec_first, rec_others, test_string, {' '});
    EXPECT_EQ(false, is_ok);
    EXPECT_STREQ(first.data(), rec_first.data());
    EXPECT_STREQ(others.data(), rec_others.data());
}
TEST(analyzer_utils, delim_string_positive)
{
    std::string test_string = "first word";
    std::string first = "first";
    std::string others = "word";
    std::string rec_first, rec_others;

    bool is_ok = IndentAnalyzerUtils::delimString(rec_first, rec_others, test_string, {' '});
    EXPECT_EQ(true, is_ok);
    EXPECT_STREQ(first.data(), rec_first.data());
    EXPECT_STREQ(others.data(), rec_others.data());
}
TEST(analyzer_utils, cut_front_positive)
{
    std::string test_string("Useless text Usefull text");
    std::string ult("Useless text");
    std::string uft(" Usefull text");

    std::string answer = IndentAnalyzerUtils::cutFront(test_string, ult.size());
    EXPECT_STREQ(answer.data(), uft.data());
}
TEST(analyzer_utils, skip_symbols_positive)
{
    std::string str(" \t qwer");
    std::vector<char> syms = {' ', '\t'};

    EXPECT_STREQ("qwer", IndentAnalyzerUtils::skipSymbols(str, syms).data());
}
TEST(analyzer_utils, skip_symbols_negative)
{
    std::string str("qwer");
    std::vector<char> syms = {' ', '\t'};

    EXPECT_STREQ("qwer", IndentAnalyzerUtils::skipSymbols(str, syms).data());
}
TEST(analyzer_utils, skip_symbols_any_delim)
{
    std::string str("qwer");
    std::vector<char> syms = {'q', 'w', 'e', 'r'};

    EXPECT_STREQ("", IndentAnalyzerUtils::skipSymbols(str, syms).data());
}
TEST(memory, merge_positive)
{
    auto memory = new Memory(State::Alg, new PAlgorithm("text"));
    auto merged_memory = new Memory(State::Fork, new PFork("text"));

    EXPECT_EQ(0, memory->getComplexPrimitive()->childrenNum());
    memory->merge(merged_memory);
    EXPECT_EQ(1, memory->getComplexPrimitive()->childrenNum());
    EXPECT_EQ(nullptr, merged_memory);

    delete memory;
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop

