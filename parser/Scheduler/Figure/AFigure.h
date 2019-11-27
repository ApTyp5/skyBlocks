//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_AFIGURE_H_
#define PARSER_SCHEDULER_FIGURE_AFIGURE_H_

#include <string>

struct Point
{
    size_t x, y;
};

struct Rect
{
    Point center;
    size_t width, height;
};

class AFigure
{
public:
    explicit AFigure(std::string text, size_t page = 1)
        : text(std::move(text)), page(page)
    {}

    size_t getPage() const
    { return page; }

private:
    size_t page;
    std::string text;
};

#endif //PARSER_SCHEDULER_FIGURE_AFIGURE_H_
