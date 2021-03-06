#ifndef DESKTOP_APP_BLOCK_H
#define DESKTOP_APP_BLOCK_H

#pragma once

#include "Figure.h"

#include <string>
#include <vector>

struct BlockData : public FigureData {
    std::string blockType;
    double centerPosX;
    double centerPosY;
    double rectangleWidth;
    double rectangleHeight;
    std::string innerText;

    BlockData() : blockType(), centerPosX(0), centerPosY(0),
        rectangleWidth(0), rectangleHeight(0), innerText() {}
};

class Block : public Figure {
public:
    explicit Block() : centerPosX(0), centerPosY(0), rectangleWidth(0),
        rectangleHeight(0), innerText() {}
    virtual ~Block() override {}

    double getPositionX() const { return centerPosX; }
    double getPositionY() const { return centerPosY; }
    double getWidth() const { return rectangleWidth; }
    double getHeight() const { return  rectangleHeight; }
    std::string getText() const { return innerText; }


    void setPositionX(const double &value) { centerPosX = value; }
    void setPositionY(const double &value) { centerPosY = value; }
    void setWidth(const double &value) { rectangleWidth = value; }
    void setHeight(const double &value) { rectangleHeight = value; }
    void setText(const std::string &value) { innerText = value; }

    virtual DrawData *Draw() override;
protected:
    double centerPosX;
    double centerPosY;
    double rectangleWidth;
    double rectangleHeight;
    std::string innerText;
};

#endif //DESKTOP_APP_BLOCK_H
