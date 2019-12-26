//
// Created by arthur on 23.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_TOOLS_UTILS_H_
#define PARSER_ANALYZER_INDENTANALYZE_TOOLS_UTILS_H_

#include "../../Primitive/APrimitive.h"
#include "../../Primitive/PAlgorithm.h"
#include "../../Primitive/PCycle.h"
#include "../../Primitive/PFollow.h"
#include "../../Primitive/PFork.h"
#include "States.h"

class IndentAnalyzerUtils
{
public:
    static APrimitive *createPrimitive(State state,
                                       const std::wstring &par1 = L"",
                                       const std::wstring &par2 = L"")
    {
        switch (state) {
            case State::Alg:return new PAlgorithm(par1);
            case State::Follow: return new PFollow(par1);
            case State::Fork: return new PFork(par1);
            case State::Cycle: return new PCycle(par1, par2);
            case State::UnknownIndent:throw std::exception();
        }
    };

    static std::wstring cutFront(const std::wstring &str, size_t size)
    {
        return str.substr(size);
    }

    static bool delimString(std::wstring &firstWord, std::wstring &others, const std::wstring &str,
                            const std::vector<wchar_t> &delims = {L' '})
    {
        return separateString(firstWord, others, str, delims);
    }

    static std::wstring strAppendMultipleSymbols(const std::wstring &curIndent, wchar_t sym, size_t n)
    {
        std::wstring output(curIndent);
        for (size_t i = 0; i < n; i++) {
            output += sym;
        }
        return output;
    }

    template<typename T>
    static bool isInVector(T el, const std::vector<T> &vector)
    {
        for (auto &i : vector) {
            if (i == el)
                return true;
        }

        return false;
    }

    static std::wstring skipBorderSymbols(const std::wstring &str, const std::vector<wchar_t> &syms)
    {
        return skipBackSymbols(skipSymbols(str, syms), syms);
    }

    static std::wstring skipSymbols(const std::wstring &str, const std::vector<wchar_t> &syms)
    {
        for (size_t i = 0; i < str.size(); i++) {
            if (!isInVector(str[i], syms))
                return str.substr(i);
        }

        return std::wstring();
    }

    static std::wstring skipBackSymbols(const std::wstring &str, const std::vector<wchar_t> &syms)
    {
        for (size_t i = str.size() - 1; i >= 0; i--) {
            if (!isInVector(str[i], syms))
                return str.substr(0, i + 1);
        }

        return std::wstring();
    }

    static bool extractFirstWord(std::wstring &fWord, const std::wstring &str, const std::vector<wchar_t> &delims)
    {
        std::wstring sPart;
        return separateString(fWord, sPart, str, delims);
    }

    static bool extractSecondWord(std::wstring &sWord, const std::wstring &str, const std::vector<wchar_t> &delims)
    {
        std::wstring fPart, sPart;
        bool ans = separateString(fPart, sPart, str, delims);
        separateString(sWord, fPart, sPart, delims);
        return ans;
    }

    static void delLastNewLine(std::wstring &str)
    {
        if (str.back() == '\n')
            str.pop_back();
    }

private:
    static bool separateString(std::wstring &firstPart,
                               std::wstring &secondPart,
                               const std::wstring &initString,
                               const std::vector<wchar_t> &delims)
    {
        std::vector<size_t> pos(delims.size());
        for (size_t i = 0; i < delims.size(); i++) {
            pos[i] = (initString.find(delims[i]));
        }
        auto minEl = std::min_element(pos.begin(), pos.end());
        if (*minEl == std::wstring::npos) {
            firstPart = initString;
            return false;
        }

        firstPart = initString.substr(0, *minEl);
        secondPart = initString.substr(*minEl + 1);
        return true;
    }
};

#endif //PARSER_ANALYZER_INDENTANALYZE_TOOLS_UTILS_H_
