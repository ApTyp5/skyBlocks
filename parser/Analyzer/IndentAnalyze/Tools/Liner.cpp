//
// Created by arthur on 22.11.2019.
//

#include "Liner.h"

Liner::Liner(const std::string &text) {
  ss.str(text);
}

bool Liner::getLine(std::string &line) {
  std::getline(ss, line);
  return !ss.eof();
}


