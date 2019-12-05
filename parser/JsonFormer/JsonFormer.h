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
    explicit JsonFormer(int id = 0);

    //jsonString formJson(ptrVector<AFigure> &figures);
    jsonString formJson(const ptrVector<JsonFormable> &jf);
    jsonString formJson(const ptrVector<AFigure> &figures);
    jsonString formJson(const ptrVector<ParseError> &errors);

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
    void addAFigure(const std::string &templat, const AFigure &aFigure);
    void addSMFigure(const std::string &templat, const SingleMeasureFigure &smFigure);
    void addDMFigure(const std::string &templat, const DoubleMeasureFigure &dmFigure);
    void addAloneProperty(const std::string &path, const std::string &name);
    void addGroupProperty(const std::string &path, const std::string &name);
    std::string newFigureTemplat();
    std::string newErrorTemplat();
    void initFigureTemplat();
    void initErrorTemplat();

private:
    int id;
    std::string templat;
    boost::property_tree::ptree tree;
};

class JsonFormable
{
public:
    virtual void acceptJsonFormer(JsonFormer &jFormer) = 0;
};

#endif //PARSER_JSONFORMER_JSONFORMER_H_
