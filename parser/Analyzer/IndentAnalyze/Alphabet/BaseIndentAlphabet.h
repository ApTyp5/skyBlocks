//
// Created by arthur on 24.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_ALPHABET_BASEALPHABET_H_
#define PARSER_ANALYZER_INDENTANALYZE_ALPHABET_BASEALPHABET_H_

#include <string>
#include <vector>

class BaseIndentAlphabet
{
public:
    BaseIndentAlphabet(
        std::wstring forkWord,
        std::wstring elseWord,
        std::wstring cycleWord,
        std::wstring callFuncWord,
        std::wstring defineFuncWord,
        std::vector<wchar_t> wordDelimiters,
        std::vector<wchar_t> sectionDelimiters)
        :
        forkWord(std::move(forkWord)),
        elseWord(std::move(elseWord)),
        cycleWord(std::move(cycleWord)),
        callFuncWord(std::move(callFuncWord)),
        defineFuncWord(std::move(defineFuncWord)),
        wordDelimiters(std::move(wordDelimiters)),
        sectionDelimiters(std::move(sectionDelimiters))
    {}

    virtual const std::vector<wchar_t> &WordDelimiters()
    { return wordDelimiters; }
    virtual const std::vector<wchar_t> &SectionDelimiters()
    { return sectionDelimiters; }
    virtual const std::wstring &ForkWord()
    { return forkWord; }
    virtual const std::wstring &ElseWord()
    { return elseWord; }
    virtual const std::wstring &CycleWord()
    { return cycleWord; }
    virtual const std::wstring &CallFuncWord()
    { return callFuncWord; }
    virtual const std::wstring &DefineFuncWord()
    { return defineFuncWord; }

private:
    std::vector<wchar_t> sectionDelimiters;
    std::vector<wchar_t> wordDelimiters;
    std::wstring forkWord;
    std::wstring elseWord;
    std::wstring cycleWord;
    std::wstring callFuncWord;
    std::wstring defineFuncWord;
};
#endif //PARSER_ANALYZER_INDENTANALYZE_ALPHABET_BASEALPHABET_H_
