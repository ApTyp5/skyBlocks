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

typedef std::string jsonString;

class JsonFormer
{
public:
    jsonString addToTree(boost::property_tree::ptree &tree, FArrow &fArrow);
    jsonString addToTree(boost::property_tree::ptree &tree, FLine &fLine);
    jsonString addToTree(boost::property_tree::ptree &tree, FBegCycle &fBegCycle);
    jsonString addToTree(boost::property_tree::ptree &tree, FEndCycle &fEndCycle);
    jsonString addToTree(boost::property_tree::ptree &tree, FBegEnd &fBegEnd);
    jsonString addToTree(boost::property_tree::ptree &tree, FContinue &fContinue);
    jsonString addToTree(boost::property_tree::ptree &tree, FFollow &fFollow);
    jsonString addToTree(boost::property_tree::ptree &tree, FFork &fFork);
    jsonString addToTree(boost::property_tree::ptree &tree, FFunc &fFunc);

    jsonString formJson(ptrVector<AFigure> &figures);

protected:
    void addAloneProperty(boost::property_tree::ptree &tree, std::string path, std::string name);
    void addGroupProperty(boost::property_tree::ptree &tree, std::string path, std::string name);

};

#endif //PARSER_JSONFORMER_JSONFORMER_H_
