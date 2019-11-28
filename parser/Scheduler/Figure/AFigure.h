//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_SCHEDULER_FIGURE_AFIGURE_H_
#define PARSER_SCHEDULER_FIGURE_AFIGURE_H_

#include <string>
#include <ostream>

struct Point
{
    size_t x, y;
    bool operator==(Point p) const
    {
        return (x == p.x && y == p.y);
    }
    std::ostream &operator<<(std::ostream &out)
    {
        out << "(" << x << ", " << y << ")";
        return out;
    }
};

struct sRect
{
    size_t w, h;
    sRect operator*=(size_t num)
    {
        w *= num;
        h *= num;
        return *this;
    }
};

struct Rect
{
    Point center;
    sRect size;
};

class AFigure
{
public:
    explicit AFigure(std::string text, size_t page = 1)
        : text(std::move(text)), page(page)
    {}

    virtual ~AFigure() = default;

    size_t getPage() const
    { return page; }

    const std::string &getText()
    {
        return text;
    }

private:
    size_t page;
    std::string text;
};

#endif //PARSER_SCHEDULER_FIGURE_AFIGURE_H_
