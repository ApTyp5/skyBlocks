//
// Created by arthur on 22.11.2019.
//

#include <memory>

#include "../Analyzer/Primitive/ComplexPrimitive.h"
#include "CommonScheduler.h"


ptrVector<AFigure> CommonScheduler::schedule(const std::unique_ptr<ComplexPrimitive> &algorithm)
{
    return ptrVector<AFigure>();
}
bool CommonScheduler::schedulePrimitive(PAlgorithm &primitive, AScheduler &scheduler)
{
    return false;
}
bool CommonScheduler::schedulePrimitive(PCycle &primitive, AScheduler &scheduler)
{
    return false;
}
bool CommonScheduler::schedulePrimitive(PFollow &primitive, AScheduler &scheduler)
{
    return false;
}
bool CommonScheduler::schedulePrimitive(PFork &primitive, AScheduler &scheduler)
{
    return false;
}
bool CommonScheduler::schedulePrimitive(PFunc &primitive, AScheduler &scheduler)
{
    return false;
}

