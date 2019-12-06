#ifndef FIGURE_H
#define FIGURE_H

#pragma once

#include <string>
#include <vector>
#include <array>

enum FigureType {
    LINE = 0, BLOCK, FUNC, IF, WHILE, UNDEFINED = -1
};

struct FigureData {
    FigureType figureType;

    FigureData() : figureType(UNDEFINED) {}
};

struct DrawData {
    FigureType figureType;
    std::vector<std::array<int, 2>> points;

    DrawData() : figureType(UNDEFINED), points() {}
};

class Figure {
public:
    virtual ~Figure() = default;

    virtual void Draw() = 0;
};

#endif // FIGURE_H
