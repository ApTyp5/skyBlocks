#ifndef FIGURE_H
#define FIGURE_H

#pragma once

#include <string>
#include <vector>
#include <array>

enum FigureType {
    LINE = 0, BLOCK, FUNC, IF, WHILEBEGIN, WHILEEND, TERMINAL, UNDEFINED = -1
};

struct FigureData {
    FigureType figureType;

    int page;

    FigureData() : figureType(UNDEFINED), page(0) {}
};

struct DrawData {
    FigureType figureType;
    std::vector<std::array<int, 2>> points;
    std::string text;

    int page;

    int centerX;
    int centerY;

    int textPosX;
    int textPosY;

    DrawData() : figureType(UNDEFINED), points(), text(),
        centerX(0), centerY(0), textPosX(0), textPosY(0) {}
};

class Figure {
public:
    Figure() : page(0) {}
    virtual ~Figure() = default;

    void setPage(const int &num) { page = num; }
    int getPage() const { return page; }

    virtual DrawData *Draw() = 0;
protected:
    int page;
};

#endif // FIGURE_H
