#include "Block.h"

DrawData *Block::Draw() {
    auto data = new DrawData;
    data->figureType = BLOCK;
    int leftTopX = centerPosX - rectangleWidth / 2;
    int leftTopY = centerPosY - rectangleHeight / 2;

    data->points.push_back({
                    leftTopX,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth,
                    leftTopY + rectangleHeight
                    });
    data->points.push_back({
                    leftTopX,
                    leftTopY + rectangleHeight
                    });

    data->text = innerText;
    data->page = page;
    data->textPosX = leftTopX + 2;
    data->textPosY = leftTopY + rectangleHeight - 2;

    return data;
}
