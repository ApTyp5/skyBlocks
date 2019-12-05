//
// Created by arthur on 05.12.2019.
//

#ifndef FINDENTPYTHONLIKECONSTRAINTOR_H
#define FINDENTPYTHONLIKECONSTRAINTOR_H

#include <gtest/gtest.h>

#include "../Analyzer/IndentAnalyze/IndentConstraintor.h"
#include "../Analyzer/IndentAnalyze/Tools/Memory.h"
#include "../Analyzer/IndentAnalyze/Alphabet/PythonLikeAlphabet.h"

class FIndentPythonLikeConstraintor: public ::testing::Test
{
protected:
    ptrVector<ParseError> errors;
    IndentConstraintor *constraintor;

    virtual void SetUp()
    {
        constraintor = new IndentConstraintor(errors, new PythonLikeAlphabet);
    }

    virtual void TearDown()
    {
        delete constraintor;
    }
};

#endif //FINDENTPYTHONLIKECONSTRAINTOR_H
