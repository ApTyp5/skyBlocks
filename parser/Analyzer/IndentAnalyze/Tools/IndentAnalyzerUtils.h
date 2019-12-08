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
                                       const std::string &par1 = "",
                                       const std::string &par2 = "")
    {
        switch (state) {
            case State::Alg:return new PAlgorithm(par1);
            case State::Follow: return new PFollow(par1);
            case State::Fork: return new PFork(par1);
            case State::Cycle: return new PCycle(par1, par2);
            case State::UnknownIndent:throw std::exception();
        }
    };

    static std::string cutFront(const std::string &str, size_t size)
    {
        return str.substr(size);
    }

    static bool delimString(std::string &firstWord, std::string &others, const std::string &str,
                            const std::vector<char> &delims = {' '})
    {
        return separateString(firstWord, others, str, delims);
    }

    static std::string strAppendMultipleSymbols(const std::string &curIndent, char sym, size_t n)
    {
        std::string output(curIndent);
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

    static std::string skipBorderSymbols(const std::string &str, const std::vector<char> &syms)
    {
        return skipBackSymbols(skipSymbols(str, syms), syms);
    }

    static std::string skipSymbols(const std::string &str, const std::vector<char> &syms)
    {
        for (size_t i = 0; i < str.size(); i++) {
            if (!isInVector(str[i], syms))
                return str.substr(i);
        }

        return std::string();
    }

    static std::string skipBackSymbols(const std::string &str, const std::vector<char> &syms)
    {
        for (size_t i = str.size() - 1; i >= 0; i--) {
            if (!isInVector(str[i], syms))
                return str.substr(0, i + 1);
        }

        return std::string();
    }

    static bool extractFirstWord(std::string &fWord, const std::string &str, const std::vector<char> &delims)
    {
        std::string sPart;
        return separateString(fWord, sPart, str, delims);
    }

    static bool extractSecondWord(std::string &sWord, const std::string &str, const std::vector<char> &delims)
    {
        std::string fPart, sPart;
        bool ans = separateString(fPart, sPart, str, delims);
        separateString(sWord, fPart, sPart, delims);
        return ans;
    }

    static void delLastNewLine(std::string &str)
    {
        if (str.back() == '\n')
            str.pop_back();
    }

private:
    static bool separateString(std::string &firstPart,
                               std::string &secondPart,
                               const std::string &initString,
                               const std::vector<char> &delims)
    {
        std::vector<size_t> pos(delims.size());
        for (size_t i = 0; i < delims.size(); i++) {
            pos[i] = (initString.find(delims[i]));
        }
        auto minEl = std::min_element(pos.begin(), pos.end());
        if (*minEl == std::string::npos) {
            firstPart = initString;
            return false;
        }

        firstPart = initString.substr(0, *minEl);
        secondPart = initString.substr(*minEl + 1);
        return true;
    }
};

#endif //PARSER_ANALYZER_INDENTANALYZE_TOOLS_UTILS_H_
