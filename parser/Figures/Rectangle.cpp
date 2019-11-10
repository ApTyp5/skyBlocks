//
// Created by arthur on 09.11.2019.
//

#include "Rectangle.h"

Rectangle::Rectangle(Rect rect, std::string text):
  DoubleMeasureFigure(rect, text){}

std::string toJson() { return "Rectangle"; }
