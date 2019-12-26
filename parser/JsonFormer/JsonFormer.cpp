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

void JsonFormer::addSection(const ptrVector<JsonFormable> &vector, const std::wstring &section)
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
        addSection((const ptrVector<JsonFormable> &) vector, L"figure");
}
void JsonFormer::addErrors(const ptrVector<ParseError> &vector)
{
    if (vector.size())
        addSection((const ptrVector<JsonFormable> &) vector, L"error");
}
void JsonFormer::childAddProperty(const std::wstring &path, const std::wstring &name)
{
    child.add(path, name);
}
void JsonFormer::addAFigure(const AFigure &aFigure)
{
    childAddProperty(std::wstring(L"text"), aFigure.getText());
    childAddProperty(std::wstring(L"page"), std::to_wstring(aFigure.getPage()));
    childAddProperty(std::wstring(L"type"), aFigure.figureType());
}
void JsonFormer::addSMFigure(const SingleMeasureFigure &smFigure)
{
    childAddProperty(std::wstring(L"begin.x"), std::to_wstring(smFigure.getBegin().x));
    childAddProperty(std::wstring(L"begin.y"), std::to_wstring(smFigure.getBegin().y));
    childAddProperty(std::wstring(L"end.x"), std::to_wstring(smFigure.getEnd().x));
    childAddProperty(std::wstring(L"end.y"), std::to_wstring(smFigure.getEnd().y));
    addAFigure(smFigure);
}
void JsonFormer::addDMFigure(const DoubleMeasureFigure &dmFigure)
{
    childAddProperty(std::wstring(L"size.width"), std::to_wstring(dmFigure.getWidth()));
    childAddProperty(std::wstring(L"size.height"), std::to_wstring(dmFigure.getHeight()));
    childAddProperty(std::wstring(L"center.x"), std::to_wstring(dmFigure.getCenter().x));
    childAddProperty(std::wstring(L"center.y"), std::to_wstring(dmFigure.getCenter().y));
    addAFigure(dmFigure);
}

void JsonFormer::addToJson(const FLine &fLine)
{
    child.clear();
    addSMFigure(fLine);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const FArrow &fArrow)
{
    child.clear();
    addSMFigure(fArrow);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const FBegCycle &fBegCycle)
{
    child.clear();
    addDMFigure(fBegCycle);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const FEndCycle &fEndCycle)
{
    child.clear();
    addDMFigure(fEndCycle);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const FBegEnd &fBegEnd)
{
    child.clear();
    addDMFigure(fBegEnd);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const FContinue &fContinue)
{
    child.clear();
    addDMFigure(fContinue);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const FFollow &fFollow)
{
    child.clear();
    addDMFigure(fFollow);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const FFork &fFork)
{
    child.clear();
    addDMFigure(fFork);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const FFunc &fFunc)
{
    child.clear();
    addDMFigure(fFunc);
    children.push_back(std::make_pair(L"", child));
}
void JsonFormer::addToJson(const ParseError &error)
{
    child.clear();
    childAddProperty(std::wstring(L"row"), std::to_wstring(error.getRow()));
    childAddProperty(std::wstring(L"col"), std::to_wstring(error.getCol()));
    childAddProperty(std::wstring(L"text"), error.getMessage());
    children.push_back(std::make_pair(L"", child));
}
jsonString JsonFormer::getJson()
{
    std::wostringstream output;
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







