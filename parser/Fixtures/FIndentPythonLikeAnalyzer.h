//
// Created by arthur on 24.11.2019.
//

#ifndef FINDENTPYTHONLIKEANALYZER_H
#define FINDENTPYTHONLIKEANALYZER_H

#include <gtest/gtest.h>

#include "../Analyzer/IndentAnalyze/IndentAnalyzer.h"

class FIndentPythonLikeAnalyzer: public ::testing::Test
{
protected:
    ptrVector<ParseError> errors;
    IndentAnalyzer *analyzer;

    virtual void SetUp()
    {
        analyzer = new IndentAnalyzer(errors, new PythonLikeAlphabet);
    }

    virtual void TearDown()
    {
        delete analyzer;
    }
};

#endif //FINDENTPYTHONLIKEANALYZER_H
