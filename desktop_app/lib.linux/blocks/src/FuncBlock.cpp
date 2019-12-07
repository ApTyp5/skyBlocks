#include "FuncBlock.h"

DrawData *FuncBlock::Draw() {
    auto data = new DrawData;
    data->figureType = BLOCK;
    int leftTopX = centerPosX - rectangleWidth / 2;
    int leftTopY = centerPosY - rectangleHeight / 2;

    int subRectWidth = rectangleWidth / 10;

    data->points.push_back({
                    leftTopX,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + subRectWidth,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + subRectWidth,
                    leftTopY + rectangleHeight
                    });
    data->points.push_back({
                    leftTopX,
                    leftTopY + rectangleHeight
                    });
    data->points.push_back({
                    leftTopX,
                    leftTopY
                    });

    data->points.push_back({
                    leftTopX + subRectWidth,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth - subRectWidth,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth - subRectWidth,
                    leftTopY + rectangleHeight
                    });
    data->points.push_back({
                    leftTopX + subRectWidth,
                    leftTopY + rectangleHeight
                    });
    data->points.push_back({
                    leftTopX + subRectWidth,
                    leftTopY
                    });

    data->points.push_back({
                    leftTopX + rectangleWidth - subRectWidth,
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
                    leftTopX + rectangleWidth - subRectWidth,
                    leftTopY + rectangleHeight
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth - subRectWidth,
                    leftTopY
                    });

    data->text = innerText;
    data->textPosX = leftTopX + subRectWidth + 3;
    data->textPosY = leftTopY + rectangleHeight - 2;

    return data;
}
