//
// Created by arthur on 09.11.2019.
//

#include "BegEnd.h"

BegEnd::BegEnd(Rect rect, std::string text):
  DoubleMeasureFigure(rect, text){}

std::string toJson() { return "begEnd"; }
std::string BegEnd::toJson() const {
  return std::__cxx11::string();
}
