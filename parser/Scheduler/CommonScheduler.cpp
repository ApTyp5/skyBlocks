//
// Created by arthur on 22.11.2019.
//

#include <memory>

#include "../Analyzer/Primitive/ComplexPrimitive.h"
#include "CommonScheduler.h"

ptrVector<AFigure> CommonScheduler::schedule(const std::unique_ptr<ComplexPrimitive> &algorithm, Meta meta)
{
    size_t width = meta.getWidth() - 2 * meta.getXMargin();
    size_t height = meta.getHeight() - 2 * meta.getYMargin();
    size_t kegel = meta.getKegel();
    size_t symWidth = meta.getSymWidth();

    ptrVector<AFigure> output;
    size_t x = width / 2;
    size_t y = 0;

    put(algorithm.get(), x, y, height);

    return output;
}

void CommonScheduler::put(APrimitive *primitive, size_t curX, size_t curY, size_t maxY)
{

}

void CommonScheduler::put(ComplexPrimitive *primitive, size_t curX, size_t curY, size_t maxY)
{
    const ptrVector<APrimitive> &children = primitive->getChildern();
}

