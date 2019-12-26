//
// Created by arthur on 27.11.2019.
//
#include "FContinue.h"

wchar_t FContinue::name[2] = L"A";

size_t FContinue::counter = 0;

void FContinue::reset()
{
    *name = 'A';
    name[1] = 0;
    counter = 0;
}

void FContinue::acceptJsonFormer(JsonFormer &jFormer)
{
    jFormer.addToJson(*this);
}

std::wstring FContinue::figureType() const
{
    return std::wstring(L"continue");
}

FContinue::FContinue(Rect rect, size_t page)
    :
    DoubleMeasureFigure(rect, std::wstring(name), page)
{
    if (counter % 2) {
        counter = 0;
        ++*name;
    }
    else {
        counter++;
    }
}
AFigure *FContinue::tryToConvertToFBegEnd()
{
    return this;
}
