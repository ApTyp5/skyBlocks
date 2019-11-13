//
// Created by arthur on 09.11.2019.
//

#include "Cycle.h"

Cycle::Cycle(size_t innerNum, std::string topText, std::string bottomText):
  AbstractPrimitive(topText), bottomText(bottomText), innnerNum(innerNum){}

AbstractFigure *Cycle::toFigure(const Rect &rect) const {
  return nullptr;
}
