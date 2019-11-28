//
// Created by arthur on 27.11.2019.
//

#ifndef FIGURECREATOR_H
#define FIGURECREATOR_H

#include <exception>
#include <utility>
#include "FigureTypes.h"
#include "FArrorw.h"
#include "FBegCycle.h"
#include "FEndCycle.h"
#include "FFollow.h"
#include "FFork.h"
#include "FFunc.h"

class FigureCreator
{
public:
    static AFigure *createDMF(FigureType type, Rect rect, std::string text, size_t page = 1)
    {
        switch (type) {
            case BegCycle: return new FBegCycle(rect, std::move(text), page);
            case EndCycle: return new FEndCycle(rect, std::move(text), page);
            case Follow: return new FFollow(rect, std::move(text), page);
            case Fork: return new FFork(rect, std::move(text), page);
            case Func: return new FFunc(rect, std::move(text), page);
            default: throw std::exception();
        }
    }
};
#endif //FIGURECREATOR_H
