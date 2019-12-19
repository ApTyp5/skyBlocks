#include "IfBlock.h"

DrawData *IfBlock::Draw() {
    auto data = new DrawData;

    data->figureType = BLOCK;
    int leftTopX = centerPosX - rectangleWidth / 2;
    int leftTopY = centerPosY;

    data->points.push_back(
                std::array<int, 2>({
                    leftTopX,
                    leftTopY
                                   })
                );
    data->points.push_back(
                std::array<int, 2>({
                    leftTopX + rectangleWidth / 2,
                    leftTopY - rectangleHeight / 2
                                   })
                );
    data->points.push_back(
                std::array<int, 2>({
                    leftTopX + rectangleWidth,
                    leftTopY
                                   })
                );
    data->points.push_back(
                std::array<int, 2>({
                    leftTopX + rectangleWidth / 2,
                    leftTopY + rectangleHeight / 2
                                   })
                );

    data->page = page;
    data->text = innerText;

    data->centerX = centerPosX;
    data->centerY = centerPosY;
    data->width = rectangleWidth;
    data->height = rectangleHeight;

    return data;
}
