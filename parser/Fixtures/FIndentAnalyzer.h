//
// Created by arthur on 24.11.2019.
//

#ifndef FINDENTANALYZER_H
#define FINDENTANALYZER_H

#include <gtest/gtest.h>

#include "../Analyzer/IndentAnalyze/IndentAnalyzer.h"

class FIndentAnalyzer: public ::testing::Test
{
protected:
    ptrVector<Error> errors;
    IndentAnalyzer *analyzer;

    virtual void SetUp()
    {
        analyzer = new IndentAnalyzer(errors);
        analyzer->longMemory.push_back(new Memory(State::Alg, new PAlgorithm("")));

    }

    virtual void TearDown()
    {
        delete analyzer;
    }
};
#endif //FINDENTANALYZER_H
