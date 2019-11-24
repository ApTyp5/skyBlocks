//
// Created by arthur on 24.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_TOOLS_MEMORY_H_
#define PARSER_ANALYZER_INDENTANALYZE_TOOLS_MEMORY_H_

#include <string>

#include "../../Primitive/ComplexPrimitive.h"
#include "States.h"


class Memory
{
    State state_;
    std::string bodyIndent;
    ComplexPrimitive *complexPrimitive;

public:
    Memory(State state, ComplexPrimitive *complex_primitive);
    Memory(Memory &&memory) noexcept;

    void merge(Memory *&memory);

public:
    State getState() const;
    const std::string &getBodyIndent() const;
    ComplexPrimitive *getComplexPrimitive() const;

public:
    void setBodyIndent(const std::string &indent);
};

#endif //PARSER_ANALYZER_INDENTANALYZE_TOOLS_MEMORY_H_
