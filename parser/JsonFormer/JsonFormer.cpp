//
// Created by arthur on 22.11.2019.
//
#include <ostream>
#include "JsonFormer.h"
#include "../Scheduler/Figure/DoubleMeasureFigure.h"
#include "../Scheduler/Figure/FBegCycle.h"
#include "../Scheduler/Figure/FEndCycle.h"
#include "../Scheduler/Figure/FBegEnd.h"
#include "../Scheduler/Figure/FArrorw.h"
#include "../Scheduler/Figure/FLine.h"
#include "../Scheduler/Figure/FContinue.h"
#include "../Scheduler/Figure/FFollow.h"
#include "../Scheduler/Figure/FFork.h"
#include "../Scheduler/Figure/FFunc.h"
#include "../Errors/ParseError.h"

void JsonFormer::addSection(const ptrVector<JsonFormable> &vector, const std::string &section)
{
    children.clear();
    for (const auto &i : vector) {
        i->acceptJsonFormer(*this);
    }

    if (!children.empty())
        tree.add_child(section, children);
}
void JsonFormer::addFigures(const ptrVector<AFigure> &vector)
{
    if (vector.size())
        addSection((const ptrVector<JsonFormable> &) vector, "figure");
}
void JsonFormer::addErrors(const ptrVector<ParseError> &vector)
{
    if (vector.size())
        addSection((const ptrVector<JsonFormable> &) vector, "error");
}
void JsonFormer::childAddProperty(const std::string &path, const std::string &name)
{
    child.add(path, name);
}
void JsonFormer::addAFigure(const AFigure &aFigure)
{
    childAddProperty(std::string("text"), aFigure.getText());
    childAddProperty(std::string("page"), std::to_string(aFigure.getPage()));
    childAddProperty(std::string("type"), aFigure.figureType());
}
void JsonFormer::addSMFigure(const SingleMeasureFigure &smFigure)
{
    childAddProperty(std::string("begin.x"), std::to_string(smFigure.getBegin().x));
    childAddProperty(std::string("begin.y"), std::to_string(smFigure.getBegin().y));
    childAddProperty(std::string("end.x"), std::to_string(smFigure.getEnd().x));
    childAddProperty(std::string("end.y"), std::to_string(smFigure.getEnd().y));
    addAFigure(smFigure);
}
void JsonFormer::addDMFigure(const DoubleMeasureFigure &dmFigure)
{
    childAddProperty(std::string("size.width"), std::to_string(dmFigure.getWidth()));
    childAddProperty(std::string("size.height"), std::to_string(dmFigure.getHeight()));
    childAddProperty(std::string("center.x"), std::to_string(dmFigure.getCenter().x));
    childAddProperty(std::string("center.y"), std::to_string(dmFigure.getCenter().y));
    addAFigure(dmFigure);
}

void JsonFormer::addToJson(const FLine &fLine)
{
    child.clear();
    addSMFigure(fLine);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const FArrow &fArrow)
{
    child.clear();
    addSMFigure(fArrow);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const FBegCycle &fBegCycle)
{
    child.clear();
    addDMFigure(fBegCycle);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const FEndCycle &fEndCycle)
{
    child.clear();
    addDMFigure(fEndCycle);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const FBegEnd &fBegEnd)
{
    child.clear();
    addDMFigure(fBegEnd);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const FContinue &fContinue)
{
    child.clear();
    addDMFigure(fContinue);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const FFollow &fFollow)
{
    child.clear();
    addDMFigure(fFollow);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const FFork &fFork)
{
    child.clear();
    addDMFigure(fFork);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const FFunc &fFunc)
{
    child.clear();
    addDMFigure(fFunc);
    children.push_back(std::make_pair("", child));
}
void JsonFormer::addToJson(const ParseError &error)
{
    child.clear();
    childAddProperty(std::string("row"), std::to_string(error.getRow()));
    childAddProperty(std::string("col"), std::to_string(error.getCol()));
    childAddProperty(std::string("text"), error.getMessage());
    children.push_back(std::make_pair("", child));
}
jsonString JsonFormer::getJson()
{
    std::ostringstream output;
    boost::property_tree::write_json(output, tree);
    return output.str();
}


/*jsonString JsonFormer::formJson(const ptrVector<AFigure> &figures)
{
    return addErrors(dynamic_cast<const ptrVector<JsonFormable> &>(figures));
}
jsonString JsonFormer::addSection(const ptrVector<ParseError> &errors)
{
    return addFigures(dynamic_cast<const ptrVector<JsonFormable> &>(errors));
}*/







