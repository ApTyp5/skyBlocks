//
// Created by arthur on 09.11.2019.
//

#include "Line.h"

Line::Line(Point begin, Point end, std::string sign):
  OneMeasureFigure(begin, end, sign){}


std::string toJson() { return " line "; }