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

jsonString JsonFormer::formJson(const ptrVector<JsonFormable> &jf)
{
    std::ostringstream output;

    for (const auto &i : jf) {
        i->acceptJsonFormer(*this);
    }

    boost::property_tree::write_json(output, tree);

    return output.str();
}

void JsonFormer::addAloneProperty(const std::string &path, const std::string &name)
{
    tree.put(path, name);
}
void JsonFormer::addGroupProperty(const std::string &path, const std::string &name)
{
    tree.add(path, name);
}

JsonFormer::JsonFormer(int id)
    : id(id)
{}
std::string JsonFormer::newFigureTemplat()
{
    return "figure." + std::to_string(id++) + ".";
}
std::string JsonFormer::newErrorTemplat()
{
    return "error." + std::to_string(id++) + ".";
}
void JsonFormer::addAFigure(const std::string &templat, const AFigure &aFigure)
{
    addGroupProperty(templat + std::string("text"), aFigure.getText());
    addGroupProperty(templat + std::string("page"), std::to_string(aFigure.getPage()));
    addGroupProperty(templat + std::string("type"), aFigure.figureType());
}
void JsonFormer::addSMFigure(const std::string &templat, const SingleMeasureFigure &smFigure)
{
    addGroupProperty(templat + std::string("begin.x"), std::to_string(smFigure.getBegin().x));
    addGroupProperty(templat + std::string("begin.y"), std::to_string(smFigure.getBegin().y));
    addGroupProperty(templat + std::string("end.x"), std::to_string(smFigure.getEnd().x));
    addGroupProperty(templat + std::string("end.y"), std::to_string(smFigure.getEnd().y));
    addAFigure(templat, smFigure);
}
void JsonFormer::addDMFigure(const std::string &templat, const DoubleMeasureFigure &dmFigure)
{
    addGroupProperty(templat + std::string("size.width"), std::to_string(dmFigure.getWidth()));
    addGroupProperty(templat + std::string("size.height"), std::to_string(dmFigure.getHeight()));
    addGroupProperty(templat + std::string("center.x"), std::to_string(dmFigure.getCenter().x));
    addGroupProperty(templat + std::string("center.y"), std::to_string(dmFigure.getCenter().y));
    addAFigure(templat, dmFigure);
}

void JsonFormer::addToJson(const FLine &fLine)
{
    initFigureTemplat();
    addSMFigure(templat, fLine);
}
void JsonFormer::addToJson(const FArrow &fArrow)
{
    initFigureTemplat();
    addSMFigure(templat, fArrow);
}
void JsonFormer::addToJson(const FBegCycle &fBegCycle)
{
    initFigureTemplat();
    addDMFigure(templat, fBegCycle);
}
void JsonFormer::addToJson(const FEndCycle &fEndCycle)
{
    initFigureTemplat();
    addDMFigure(templat, fEndCycle);
}
void JsonFormer::addToJson(const FBegEnd &fBegEnd)
{
    initFigureTemplat();
    addDMFigure(templat, fBegEnd);
}
void JsonFormer::addToJson(const FContinue &fContinue)
{
    initFigureTemplat();
    addDMFigure(templat, fContinue);
}
void JsonFormer::addToJson(const FFollow &fFollow)
{
    initFigureTemplat();
    addDMFigure(templat, fFollow);
}
void JsonFormer::addToJson(const FFork &fFork)
{
    initFigureTemplat();
    addDMFigure(templat, fFork);
}
void JsonFormer::addToJson(const FFunc &fFunc)
{
    initFigureTemplat();
    addDMFigure(templat, fFunc);
}
void JsonFormer::initFigureTemplat()
{
    templat = newFigureTemplat();
}
void JsonFormer::initErrorTemplat()
{
    templat = newErrorTemplat();
}
void JsonFormer::addToJson(const ParseError &error)
{
    initErrorTemplat();
    addGroupProperty(templat + std::string("row"), std::to_string(error.getRow()));
    addGroupProperty(templat + std::string("col"), std::to_string(error.getCol()));
    addGroupProperty(templat + std::string("text"), error.getMessage());
}
jsonString JsonFormer::formJson(const ptrVector<AFigure> &figures)
{
    return formJson(dynamic_cast<const ptrVector<JsonFormable> &>(figures));
}
jsonString JsonFormer::formJson(const ptrVector<ParseError> &errors)
{
    return formJson(dynamic_cast<const ptrVector<JsonFormable> &>(errors));
}







