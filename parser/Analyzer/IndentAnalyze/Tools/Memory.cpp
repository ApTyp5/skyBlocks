//
// Created by arthur on 24.11.2019.
//

#include "Memory.h"

#include <utility>

Memory::Memory(State state, ComplexPrimitive *complex_primitive)
    :
    state_(state), complexPrimitive(complex_primitive)
{}

Memory::Memory(Memory &&memory) noexcept
{
    state_ = memory.state_;
    bodyIndent = std::move(memory.bodyIndent);
    complexPrimitive = memory.complexPrimitive;
    memory.complexPrimitive = nullptr;
}

void Memory::merge(Memory *&memory)
{
    if (memory == nullptr)
        throw std::exception();

    complexPrimitive->addChild(memory->complexPrimitive);
    memory->complexPrimitive = nullptr;
    delete memory;
    memory = nullptr;
}

State Memory::getState() const
{
    return state_;
}

const std::string &Memory::getBodyIndent() const
{
    return bodyIndent;
}

ComplexPrimitive *Memory::getComplexPrimitive() const
{
    return complexPrimitive;
}

void Memory::setBodyIndent(const std::string &indent)
{
    Memory::bodyIndent = indent;
}

