//
// Created by arthur on 27.11.2019.
//
#include "FContinue.h"

char FContinue::name[2] = "A";

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

std::string FContinue::figureType() const
{
    return std::string("continue");
}

FContinue::FContinue(Rect rect, size_t page)
    :
    DoubleMeasureFigure(rect, std::string(name), page)
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
