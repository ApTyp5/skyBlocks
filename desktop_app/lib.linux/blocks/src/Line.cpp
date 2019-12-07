#include "Line.h"

DrawData *Line::Draw() {
    auto data = new DrawData;
    data->figureType = LINE;
    data->points.push_back(
                std::array<int, 2>({
                    beginX,
                    beginY
                    })
                );
    data->points.push_back(
                std::array<int, 2>({
                    endX,
                    endY
                    })
                );

    if (!text.empty()) {
        data->text = text;

        data->textPosX = ((beginX > endX) ? endX : beginX) + 3;
        data->textPosY = beginY-2;
    }

    return data;
}
