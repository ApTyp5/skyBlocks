#ifndef FIGURE_H
#define FIGURE_H

#pragma once

#include <string>
#include <vector>
#include <array>

enum FigureType {
    LINE = 0, BLOCK, FUNC, IF, WHILE, TERMINAL, UNDEFINED = -1
};

struct FigureData {
    FigureType figureType;

    FigureData() : figureType(UNDEFINED) {}
};

struct DrawData {
    FigureType figureType;
    std::vector<std::array<int, 2>> points;
    std::string text;

    DrawData() : figureType(UNDEFINED), points(), text() {}
};

class Figure {
public:
    virtual ~Figure() = default;

    virtual DrawData *Draw() = 0;
};

#endif // FIGURE_H
