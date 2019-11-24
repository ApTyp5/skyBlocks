//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_PALGORITHM_H_
#define PARSER_PRIMITIVE_PALGORITHM_H_

#include "ComplexPrimitive.h"

class PAlgorithm: public ComplexPrimitive
{
public:
    PAlgorithm(std::string name, std::string text)
        :
        ComplexPrimitive(std::move(text)), name(std::move(name))
    {}

private:
    std::string name;
};

#endif //PARSER_PRIMITIVE_PALGORITHM_H_
