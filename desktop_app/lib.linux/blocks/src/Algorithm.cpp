#include "Algorithm.h"

void Algorithm::Draw() {
    for (auto figure: figures)
        figure->Draw();
}

void Algorithm::Add(Figure *figure) {
    figures.push_back(figure);
}
