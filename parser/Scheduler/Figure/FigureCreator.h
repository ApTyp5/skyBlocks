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
            case FigureType::BegCycle: return new FBegCycle(rect, std::move(text), page);
            case FigureType::EndCycle: return new FEndCycle(rect, std::move(text), page);
            case FigureType::Follow: return new FFollow(rect, std::move(text), page);
            case FigureType::Fork: return new FFork(rect, std::move(text), page);
            case FigureType::Func: return new FFunc(rect, std::move(text), page);
            default: throw std::exception();
        }
    }
};
#endif //FIGURECREATOR_H
