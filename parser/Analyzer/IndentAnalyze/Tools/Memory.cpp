//
// Created by arthur on 24.11.2019.
//

#include "Memory.h"

Memory::Memory(State state, ComplexPrimitive *complex_primitive)
    :
    state_(state), complexPrimitive(complex_primitive)
{}

Memory::Memory(Memory &&memory) noexcept
{
    state_ = memory.state_;
    indent = std::move(memory.indent);
    complexPrimitive = memory.complexPrimitive;
    memory.complexPrimitive = nullptr;
}

void Memory::merge(Memory *memory)
{
    if (memory == nullptr)
        throw std::exception();

    complexPrimitive->addChild(memory->complexPrimitive);
    memory->complexPrimitive = nullptr;
    delete memory;
}

State Memory::getState() const
{
    return state_;
}

const std::string &Memory::getIndent() const
{
    return indent;
}

ComplexPrimitive *Memory::getComplexPrimitive() const
{
    return complexPrimitive;
}

void Memory::setIndent(const std::string &indent)
{
    Memory::indent = indent;
}
