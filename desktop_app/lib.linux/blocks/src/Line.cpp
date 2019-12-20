#include "Line.h"

DrawData *Line::Draw() {
    auto data = new DrawData;
    data->figureType = LINE;
    data->points.push_back({
                    beginX,
                    beginY
                    });
    data->points.push_back({
                    endX,
                    endY
                    });

    data->page = page;

    if (!text.empty()) {
        data->text = text;

        data->centerX = ((beginX > endX) ? endX : beginX) + 3;
        data->centerY = beginY - 2;
    }

    return data;
}
