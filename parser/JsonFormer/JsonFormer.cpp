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


jsonString JsonFormer::formJson(ptrVector<JsonFormable> &figures)
{
    std::ostringstream output;

    for (const auto &i : figures) {
        i->acceptJsonFormer(*this);
    }

    boost::property_tree::write_json(output, tree);

    return output.str();
}
void JsonFormer::addAloneProperty(std::string path, std::string name)
{
    tree.put(path, name);
}
void JsonFormer::addGroupProperty(std::string path, std::string name)
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
    std::string templat = newFigureTemplat();
    addSMFigure(templat, fLine);
}
void JsonFormer::addToJson(const FArrow &fArrow)
{
    std::string templat = newFigureTemplat();
    addSMFigure(templat, fArrow);
}
void JsonFormer::addToJson(const FBegCycle &fBegCycle)
{
    std::string templat = newFigureTemplat();
    addDMFigure(templat, fBegCycle);
}
void JsonFormer::addToJson(const FEndCycle &fEndCycle)
{
    std::string templat = newFigureTemplat();
    addDMFigure(templat, fEndCycle);
}
void JsonFormer::addToJson(const FBegEnd &fBegEnd)
{
    std::string templat = newFigureTemplat();
    addDMFigure(templat, fBegEnd);
}
void JsonFormer::addToJson(const FContinue &fContinue)
{
    std::string templat = newFigureTemplat();
    addDMFigure(templat, fContinue);
}
void JsonFormer::addToJson(const FFollow &fFollow)
{
    std::string templat = newFigureTemplat();
    addDMFigure(templat, fFollow);
}
void JsonFormer::addToJson(const FFork &fFork)
{
    std::string templat = newFigureTemplat();
    addDMFigure(templat, fFork);
}
void JsonFormer::addToJson(const FFunc &fFunc)
{
    std::string templat = newFigureTemplat();
    addDMFigure(templat, fFunc);
}






