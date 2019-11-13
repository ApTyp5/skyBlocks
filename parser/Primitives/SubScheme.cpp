//
// Created by arthur on 09.11.2019.
//

#include "SubScheme.h"

SubScheme::SubScheme(std::string text, std::string name, size_t innerBlocks):
  AbstractPrimitive(text), name(name), innerBlocks(innerBlocks){}


AbstractFigure *SubScheme::toFigure(const Rect &rect) const {
  return nullptr;
}
