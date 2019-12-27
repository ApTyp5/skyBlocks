#include "Terminal.h"

DrawData *TerminalBlock::Draw() {
    auto data = new DrawData;
    data->figureType = TERMINAL;
    double leftTopX = centerPosX - rectangleWidth / 2;
    double leftTopY = centerPosY - rectangleHeight / 2;

    data->points.push_back({
                    leftTopX + rectangleWidth / 10,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth - rectangleWidth / 10,
                    leftTopY
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth - rectangleWidth / 10,
                    leftTopY + rectangleHeight
                    });
    data->points.push_back({
                    leftTopX + rectangleWidth / 10,
                    leftTopY + rectangleHeight
                    });

    data->text = innerText;
    data->page = page;

    data->centerX = centerPosX;
    data->centerY = centerPosY;
    data->width = rectangleWidth;
    data->height = rectangleHeight;

    return data;
}
