//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_JSONFORMER_JSONFORMER_H_
#define PARSER_JSONFORMER_JSONFORMER_H_

#include <string>
#include <boost/property_tree/json_parser.hpp>
#include "../Tools/ptrVector.h"

class AFigure;
class FArrow;
class FLine;
class FBegCycle;
class FEndCycle;
class FBegEnd;
class FFollow;
class FFork;
class FFunc;
class FContinue;
class SingleMeasureFigure;
class DoubleMeasureFigure;
class ParseError;

typedef std::string jsonString;

class JsonFormable;

class JsonFormer
{
public:
    jsonString getJson();
    explicit JsonFormer();
    void addSection(const ptrVector<JsonFormable> &jf, const std::string &section);
    void addFigures(const ptrVector<AFigure> &figures);
    void addErrors(const ptrVector<ParseError> &jf);

    void addToJson(const FArrow &fArrow);
    void addToJson(const FLine &fLine);
    void addToJson(const FBegCycle &fBegCycle);
    void addToJson(const FEndCycle &fEndCycle);
    void addToJson(const FBegEnd &fBegEnd);
    void addToJson(const FContinue &fContinue);
    void addToJson(const FFollow &fFollow);
    void addToJson(const FFork &fFork);
    void addToJson(const FFunc &fFunc);
    void addToJson(const ParseError &error);

protected:
    void addAFigure(const AFigure &aFigure);
    void addSMFigure(const SingleMeasureFigure &smFigure);
    void addDMFigure(const DoubleMeasureFigure &dmFigure);
    void childAddProperty(const std::string &path, const std::string &name);

private:
    boost::property_tree::ptree tree;
    boost::property_tree::ptree children;
    boost::property_tree::ptree child;
};

class JsonFormable
{
public:
    virtual void acceptJsonFormer(JsonFormer &jFormer) = 0;
};

#endif //PARSER_JSONFORMER_JSONFORMER_H_
