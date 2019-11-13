//
// Created by arthur on 09.11.2019.
//

#include "Fork.h"

Fork::Fork(std::string text, size_t yesNum, size_t nonum):
AbstractPrimitive(text), yesNum(yesNum), noNum(nonum){}
AbstractFigure *Fork::toFigure(const Rect &rect) const {
  return nullptr;
}
