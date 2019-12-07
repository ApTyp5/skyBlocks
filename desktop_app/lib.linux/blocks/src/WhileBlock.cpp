#include "WhileBlock.h"

DrawData *WhileBlock::Draw() {
    auto data = new DrawData;
    data->figureType = BLOCK;

    int angleSize = rectangleHeight / 5;

    if (type == BEGIN) {
        int leftBotX = centerPosX - rectangleWidth / 2;
        int leftBotY = centerPosY + rectangleHeight / 2;

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

    data->text = innerText;
    data->textPosX = centerPosX - rectangleWidth / 2 + 3;
    data->textPosY = centerPosY + 3;

    return data;
}
