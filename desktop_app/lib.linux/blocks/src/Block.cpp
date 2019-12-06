#include "Block.h"

DrawData *Block::Draw() {
    auto data = new DrawData;
    data->figureType = BLOCK;
    int leftTopX = centerPosX - rectangleWidth / 2;
    int leftTopY = centerPosY - rectangleHeight / 2;

    data->points.push_back(
                std::array<int, 2>({
                    leftTopX,
                    leftTopY
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
                    leftTopX + rectangleWidth,
                    leftTopY + rectangleHeight
                                   })
                );

    data->points.push_back(
                std::array<int, 2>({
                    leftTopX,
                    leftTopY + rectangleHeight
                                   })
                );

    return data;
}
