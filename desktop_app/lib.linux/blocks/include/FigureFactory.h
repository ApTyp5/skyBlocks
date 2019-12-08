#ifndef DESKTOP_APP_BLOCKFACTORY_H
#define DESKTOP_APP_BLOCKFACTORY_H

#include "Algorithm.h"
#include "Block.h"
#include "JsonObject.h"

class FigureFactory {
public:
    FigureFactory() = default;
    ~FigureFactory() = default;

    Figure *CreateFigure(FigureData *figureData);
    Algorithm *CreateAlgorithm(const JsonObject &json);
};

#endif //DESKTOP_APP_BLOCKFACTORY_H
