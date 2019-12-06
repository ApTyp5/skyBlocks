#include "Algorithm.h"

std::vector<DrawData *> *Algorithm::DrawAll() {
    if (figures.size() == 0)
        return nullptr;

    auto data = new std::vector<DrawData *>;

    for (auto figure: figures)
        data->push_back(figure->Draw());

    return data;
}

void Algorithm::Add(Figure *figure) {
    figures.push_back(figure);
}
