#ifndef DESKTOP_APP_BLOCK_H
#define DESKTOP_APP_BLOCK_H

#pragma once

#include "Figure.h"

#include <string>
#include <vector>

struct BlockData : public FigureData {
    std::string blockType;
    int centerPosX;
    int centerPosY;
    int rectangleWidth;
    int rectangleHeight;
    std::string innerText;

    BlockData() : blockType(), centerPosX(0), centerPosY(0),
        rectangleWidth(0), rectangleHeight(0), innerText() {}
};

class Block : public Figure {
public:
    explicit Block() : centerPosX(0), centerPosY(0), rectangleWidth(0),
        rectangleHeight(0), innerText() {}
    virtual ~Block() override {}

    int getPositionX() const { return centerPosX; }
    int getPositionY() const { return centerPosY; }
    int getWidth() const { return rectangleWidth; }
    int getHeight() const { return  rectangleHeight; }
    std::string getText() const { return innerText; }


    void setPositionX(const int &value) { centerPosX = value; }
    void setPositionY(const int &value) { centerPosY = value; }
    void setWidth(const int &value) { rectangleWidth = value; }
    void setHeight(const int &value) { rectangleHeight = value; }
    void setText(const std::string &value) { innerText = value; }

    virtual DrawData *Draw() override;
protected:
    int centerPosX;
    int centerPosY;
    int rectangleWidth;
    int rectangleHeight;
    std::string innerText;
};

#endif //DESKTOP_APP_BLOCK_H
