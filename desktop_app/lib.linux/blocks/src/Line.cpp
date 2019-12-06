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

    return data;
}
