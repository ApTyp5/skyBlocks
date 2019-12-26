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
    std::wstring text = L"some text, some text\n"
                        L"moooore text\n"
                        L"\n"
                        L"ano block\n"
                        L"of\n"
                        L"text\n"
                        L"\n"
                        L"if some condition\n"
                        L"   it is multiline condition\n"
                        L"\tdo smth useless\n"
                        L"else\n"
                        L"   while top text;   \tbot text\n"
                        L"\t\tinner block\n"
                        L"   after while block\n"
                        L"after if block\n"
                        L"\n"
                        L"bye-bye block";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 1, 18));
    EXPECT_EQ(5, prim_ptr->childrenNum());
    auto *f1 = prim_ptr->getChildren()[0];
    auto *f2 = prim_ptr->getChildren()[1];
    auto if1 = dynamic_cast<const PFork *>(prim_ptr->getChildren()[2]);
    auto *f3 = prim_ptr->getChildren()[3];
    auto *f4 = prim_ptr->getChildren()[4];

    EXPECT_STREQ(L"some text, some text\nmoooore text", f1->getInnerText().data());
    EXPECT_STREQ(L"ano block\nof\ntext", f2->getInnerText().data());
    EXPECT_STREQ(L"some condition\nit is multiline condition", if1->getInnerText().data());
    EXPECT_STREQ(L"after if block", f3->getInnerText().data());
    EXPECT_STREQ(L"bye-bye block", f4->getInnerText().data());

    EXPECT_EQ(1, if1->getChildren().size());
    EXPECT_EQ(2, if1->getElseChildren().size());

    EXPECT_STREQ(L"do smth useless", if1->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ(L"after while block", if1->getElseChildren()[1]->getInnerText().data());

    auto *w = dynamic_cast<const PCycle *>(if1->getElseChildren()[0]);
    EXPECT_STREQ(L"top text", w->getBeforeCycyleText().data());
    EXPECT_STREQ(L"bot text", w->getAfterCycleText().data());
    EXPECT_EQ(1, w->getChildren().size());
    EXPECT_STREQ(L"inner block", w->getChildren()[0]->getInnerText().data());
}

TEST(IndentAnalyzer, funcTest)
{
    ptrVector<ParseError> errors;
    auto *analyzer = new IndentAnalyzer(errors, new PythonLikeAlphabet);
    std::wstring text = L"begin\n"
                        L"call funcname (some args)\n"
                        L"endL";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 1, 9));
    EXPECT_EQ(3, prim_ptr->childrenNum());

    auto func = dynamic_cast<const PFunc *>(prim_ptr->getChildren()[1]);
    EXPECT_STREQ(L"funcname", func->getName().data());
    EXPECT_STREQ(L"(some args)", func->getInnerText().data());
}
TEST(IndentAnalyzer, analyze_if)
{
    ptrVector<ParseError> errors;
    auto *analyzer = new IndentAnalyzer(errors, new PythonLikeAlphabet);
    std::wstring text = L"begin\n"
                        L"if\tcond\n"
                        L"  \tcontinue cond\n"
                        L"\n"
                        L"    smth\n"
                        L"else\n"
                        L"    smth2\n"
                        L"end";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 1, 9));
    EXPECT_EQ(3, prim_ptr->childrenNum());
    EXPECT_STREQ(L"begin", prim_ptr->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ(L"cond\ncontinue cond", prim_ptr->getChildren()[1]->getInnerText().data());
    EXPECT_STREQ(L"end", prim_ptr->getChildren()[2]->getInnerText().data());

    EXPECT_EQ(false, prim_ptr->getChildren()[0]->hasChildren());
    EXPECT_EQ(true, prim_ptr->getChildren()[1]->hasChildren());
    EXPECT_EQ(false, prim_ptr->getChildren()[0]->hasChildren());

    auto iff = dynamic_cast<const PFork *>(prim_ptr->getChildren()[1]);

    EXPECT_EQ(1, iff->childrenNum());
    EXPECT_STREQ(L"smth", iff->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ(L"smth2", iff->getElseChildren()[0]->getInnerText().data());

    EXPECT_EQ(false, iff->getChildren()[0]->hasChildren());
    EXPECT_EQ(false, iff->getElseChildren()[0]->hasChildren());
}
TEST(IndentAnalyzer, analyze_cycle)
{
    ptrVector<ParseError> errors;
    auto *analyzer = new IndentAnalyzer(errors, new PythonLikeAlphabet);
    std::wstring text = L"begin\n"
                        L"while top word; botword\n"
                        L"      more bot words\n"
                        L"    smth\n"
                        L"\n"
                        L"    smth2\n"
                        L"end\n";

    std::unique_ptr<ComplexPrimitive> prim_ptr(analyzer->analyze(text, 1, 8));
    EXPECT_EQ(3, prim_ptr->childrenNum());
    EXPECT_STREQ(L"begin", prim_ptr->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ(L"top word", prim_ptr->getChildren()[1]->getInnerText().data());
    EXPECT_STREQ(L"end", prim_ptr->getChildren()[2]->getInnerText().data());

    EXPECT_EQ(false, prim_ptr->getChildren()[0]->hasChildren());
    EXPECT_EQ(true, prim_ptr->getChildren()[1]->hasChildren());
    EXPECT_EQ(false, prim_ptr->getChildren()[0]->hasChildren());

    auto whil = dynamic_cast<const PCycle *>(prim_ptr->getChildren()[1]);

    EXPECT_EQ(2, whil->childrenNum());
    EXPECT_STREQ(L"botword\nmore bot words", whil->getAfterCycleText().data());
    EXPECT_STREQ(L"top word", whil->getBeforeCycyleText().data());
    EXPECT_STREQ(L"smth", whil->getChildren()[0]->getInnerText().data());
    EXPECT_STREQ(L"smth2", whil->getChildren()[1]->getInnerText().data());

    EXPECT_EQ(false, whil->getChildren()[0]->hasChildren());
    EXPECT_EQ(false, whil->getChildren()[1]->hasChildren());

    delete analyzer;
}
TEST_F(FIndentPythonLikeAnalyzer, analyze_2_follow)
{
    std::wstring text = L"begin\n"
                        L"\n"
                        L"end\n";

    ComplexPrimitive *prim_ptr(analyzer->analyze(text, 1, 4));
    EXPECT_EQ(2, prim_ptr->childrenNum());
    EXPECT_EQ(L"begin", prim_ptr->getChildren()[0]->getInnerText());
    EXPECT_EQ(L"end", prim_ptr->getChildren()[1]->getInnerText());
}
TEST_F(FIndentPythonLikeAnalyzer, try_add_pfollow_positive)
{
    analyzer->longMemory.push_back(new Memory(State::Alg, new PAlgorithm(L"")));
    analyzer->shortMemory = L"qwer";
    EXPECT_EQ(0, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
    analyzer->tryAddPFollowToLastMem();
    EXPECT_EQ(1, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
    EXPECT_EQ(true, analyzer->shortMemory.empty());
}
TEST_F(FIndentPythonLikeAnalyzer, merge_back_mem)
{
    analyzer->longMemory.push_back(new Memory(State::Alg, new PAlgorithm(L"")));
    analyzer->longMemory.push_back(new Memory(State::Fork, new PFork(L"text")));
    EXPECT_EQ(2, analyzer->longMemory.size());
    analyzer->mergeBackMemory();
    EXPECT_EQ(1, analyzer->longMemory.size());
    EXPECT_EQ(1, analyzer->longMemory.back()->getComplexPrimitive()->childrenNum());
}
TEST_F(FIndentPythonLikeAnalyzer, ret_indent)
{
    std::wstring str = L"\t\t\tqwer";
    std::wstring indent = analyzer->retIndent(str);
    EXPECT_STREQ(L"\t\t\t", indent.data());
}
TEST_F(FIndentPythonLikeAnalyzer, get_current_indent)
{
    analyzer->longMemory.push_back(new Memory(State::Alg, new PAlgorithm(L"__main__")));
    analyzer->indent = L"qwer";
    analyzer->state_ = State::Cycle;
    EXPECT_STREQ(L"qwer", analyzer->getCurrentIndent().data());

    analyzer->state_ = State::Fork;
    EXPECT_STREQ(L"qwer", analyzer->getCurrentIndent().data());

    analyzer->state_ = State::Follow;
    analyzer->longMemory.back()->setBodyIndent(L"asdf");
    EXPECT_STREQ(L"asdf", analyzer->getCurrentIndent().data());
}
TEST_F(FIndentPythonLikeAnalyzer, is_def_positive)
{
    std::wstring input = L"def name (args)";
    EXPECT_EQ(true, analyzer->isDef(input));
}
TEST_F(FIndentPythonLikeAnalyzer, is_def_negative)
{
    std::wstring input = L"notdef name (args)";
    EXPECT_EQ(false, analyzer->isDef(input));
}
TEST_F(FIndentPythonLikeAnalyzer, is_def_negative2)
{
    std::wstring input = L" def name (args)";
    EXPECT_EQ(false, analyzer->isDef(input));
}
TEST(analyzer_utils, extract_second_word_positive2)
{
    std::vector<wchar_t> delims = {' ', '\t'};
    std::wstring str = L"qwer asdf zxcv";
    std::wstring sWord;
    EXPECT_EQ(true, IndentAnalyzerUtils::extractSecondWord(sWord, str, delims));
    EXPECT_STREQ(L"asdf", sWord.data());
}
TEST(analyzer_utils, extract_second_word_positive)
{
    std::vector<wchar_t> delims = {' ', '\t'};
    std::wstring str = L"qwer asdf";
    std::wstring sWord;
    EXPECT_EQ(true, IndentAnalyzerUtils::extractSecondWord(sWord, str, delims));
    EXPECT_STREQ(L"asdf", sWord.data());
}
TEST(analyzer_utils, extract_second_word_negative)
{
    std::vector<wchar_t> delims = {' ', '\t'};
    std::wstring str = L"qwer";
    std::wstring sWord;
    EXPECT_EQ(false, IndentAnalyzerUtils::extractSecondWord(sWord, str, delims));
}
TEST(analyzer_utils, is_in_vector_str_positive)
{
    std::vector<std::wstring> init = {L"qwer", L"asdf"};
    EXPECT_EQ(true, IndentAnalyzerUtils::isInVector(std::wstring(L"qwer"), init));
    EXPECT_EQ(false, IndentAnalyzerUtils::isInVector(std::wstring(L"zxcv"), init));
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
    std::wstring init = L"init";
    wchar_t suffix = L'/';
    size_t num = 3;

    std::wstring output = IndentAnalyzerUtils::strAppendMultipleSymbols(init, suffix, num);
    std::wstring exp_output = init + L'/' + L'/' + L'/';
    EXPECT_STREQ(exp_output.data(), output.data());
}
TEST(analyzer_utils, delim_string_negaitve)
{
    std::wstring test_string = L"longword";
    std::wstring first = L"longword";
    std::wstring others;
    std::wstring rec_first, rec_others;

    bool is_ok = IndentAnalyzerUtils::delimString(rec_first, rec_others, test_string, {' '});
    EXPECT_EQ(false, is_ok);
    EXPECT_STREQ(first.data(), rec_first.data());
    EXPECT_STREQ(others.data(), rec_others.data());
}
TEST(analyzer_utils, delim_string_positive)
{
    std::wstring test_string = L"first word";
    std::wstring first = L"first";
    std::wstring others = L"word";
    std::wstring rec_first, rec_others;

    bool is_ok = IndentAnalyzerUtils::delimString(rec_first, rec_others, test_string, {' '});
    EXPECT_EQ(true, is_ok);
    EXPECT_STREQ(first.data(), rec_first.data());
    EXPECT_STREQ(others.data(), rec_others.data());
}
TEST(analyzer_utils, cut_front_positive)
{
    std::wstring test_string(L"Useless text Usefull text");
    std::wstring ult(L"Useless text");
    std::wstring uft(L" Usefull text");

    std::wstring answer = IndentAnalyzerUtils::cutFront(test_string, ult.size());
    EXPECT_STREQ(answer.data(), uft.data());
}
TEST(analyzer_utils, skip_symbols_positive)
{
    std::wstring str(L" \t qwer");
    std::vector<wchar_t> syms = {' ', '\t'};

    EXPECT_STREQ(L"qwer", IndentAnalyzerUtils::skipSymbols(str, syms).data());
}
TEST(analyzer_utils, skip_symbols_negative)
{
    std::wstring str(L"qwer");
    std::vector<wchar_t> syms = {' ', '\t'};

    EXPECT_STREQ(L"qwer", IndentAnalyzerUtils::skipSymbols(str, syms).data());
}
TEST(analyzer_utils, skip_symbols_any_delim)
{
    std::wstring str(L"qwer");
    std::vector<wchar_t> syms = {'q', 'w', 'e', 'r'};

    EXPECT_STREQ(L"", IndentAnalyzerUtils::skipSymbols(str, syms).data());
}
TEST(memory, merge_positive)
{
    auto memory = new Memory(State::Alg, new PAlgorithm(L"text"));
    auto merged_memory = new Memory(State::Fork, new PFork(L"text"));

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

