#include "WhileBlock.h"

DrawData *WhileBlock::Draw() {
    auto data = new DrawData;
    data->figureType = BLOCK;

    double angleSize = rectangleHeight / 5;

    if (type == BEGIN) {
        double leftBotX = centerPosX - rectangleWidth / 2;
        double leftBotY = centerPosY + rectangleHeight / 2;

        data->points.push_back({
                        leftBotX,
                        leftBotY
                        });
        data->points.push_back({
                        leftBotX + rectangleWidth,
                        leftBotY
                        });
        data->points.push_back({
                        leftBotX + rectangleWidth,
                        leftBotY - rectangleHeight + angleSize
                        });
        data->points.push_back({
                        leftBotX + rectangleWidth - angleSize,
                        leftBotY - rectangleHeight
                        });
        data->points.push_back({
                        leftBotX + angleSize,
                        leftBotY - rectangleHeight
                        });
        data->points.push_back({
                        leftBotX,
                        leftBotY - rectangleHeight + angleSize
                        });
    }

    if (type == END) {
        double leftTopX = centerPosX - rectangleWidth / 2;
        double leftTopY = centerPosY - rectangleHeight / 2;

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
                        leftTopY + rectangleHeight - angleSize
                        });
        data->points.push_back({
                        leftTopX + rectangleWidth - angleSize,
                        leftTopY + rectangleHeight
                        });
        data->points.push_back({
                        leftTopX + angleSize,
                        leftTopY + rectangleHeight
                        });
        data->points.push_back({
                        leftTopX,
                        leftTopY + rectangleHeight - angleSize
                        });
    }

    data->page = page;
    data->text = innerText;
    data->centerX = centerPosX;
    data->centerY = centerPosY;
    data->width = rectangleWidth;
    data->height = rectangleHeight;

    return data;
}
