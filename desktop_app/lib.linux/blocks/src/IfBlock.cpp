#include "IfBlock.h"

DrawData *IfBlock::Draw() {
    auto data = new DrawData;

    data->figureType = IF;
    double leftTopX = centerPosX - rectangleWidth / 2;
    double leftTopY = centerPosY;

    data->points.push_back({
                    leftTopX,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth / 2,
                    leftTopY - rectangleHeight / 2
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth / 2,
                    leftTopY + rectangleHeight / 2
                    });

    data->page = page;
    data->text = innerText;

    data->centerX = centerPosX;
    data->centerY = centerPosY;
    data->width = rectangleWidth;
    data->height = rectangleHeight;

    return data;
}
