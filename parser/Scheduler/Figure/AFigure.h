//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_AFIGURE_H_
#define PARSER_SCHEDULER_FIGURE_AFIGURE_H_

struct Point {
  double x, y;
};

struct Rect {
  double width, height;
};

#include <string>

class AFigure {
 public:
  explicit AFigure(std::string text) : text(std::move(text)) {}

 private:
  std::string text;
};

#endif //PARSER_SCHEDULER_FIGURE_AFIGURE_H_
