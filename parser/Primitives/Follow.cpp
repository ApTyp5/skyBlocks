//
// Created by arthur on 09.11.2019.
//

#include "Follow.h"

Follow::Follow(std::string text): AbstractPrimitive(text) {}
AbstractFigure *Follow::toFigure(const Rect &rect) const {
  return nullptr;
}
