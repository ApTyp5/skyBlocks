#include "Continue.h"

DrawData *ContinueBlock::Draw() {
    auto data = new DrawData;
    data->figureType = PAGE_CHANGER;
    double leftTopX = centerPosX - rectangleWidth / 2;
    double leftTopY = centerPosY - rectangleHeight / 2;

    data->points.push_back({
                    leftTopX,
                    leftTopY
                    });

    data->text = innerText;
    data->page = page;

    data->centerX = centerPosX;
    data->centerY = centerPosY;
    data->width = rectangleWidth;
    data->height = rectangleHeight;

    return data;
}
