//
// Created by arthur on 09.11.2019.
//

#include "Arrow.h"

Arrow::Arrow(Point begin, Point end, std::string sign):
  OneMeasureFigure(begin, end, sign){}

std::string toJson(){ return "test"; }
std::string Arrow::toJson() const {
  return std::__cxx11::string();
}
