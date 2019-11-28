//
// Created by arthur on 24.11.2019.
//

#ifndef FIXTUREINDENTANALYZER_H
#define FIXTUREINDENTANALYZER_H

#include <gtest/gtest.h>

#include "../Analyzer/IndentAnalyze/IndentAnalyzer.h"

class FixtureIndentAnalyzer: public ::testing::Test
{
protected:
    ptrVector<Error> errors;
    IndentAnalyzer *analyzer;

    virtual void SetUp()
    {
        analyzer = new IndentAnalyzer(errors);
        analyzer->longMemory.push_back(new Memory(Alg, new PAlgorithm("")));

    }

    virtual void TearDown()
    {
        delete analyzer;
    }
};
#endif //FIXTUREINDENTANALYZER_H
