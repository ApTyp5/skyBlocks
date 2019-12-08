//
// Created by arthur on 22.11.2019.
//

#include <jmorecfg.h>
#include "Liner.h"

Liner::Liner(const std::string &text)
{
    ss.str(text);
}
bool Liner::getLine(std::string &line, bool withNL)
{
    if (ss.eof()) return false;
    std::getline(ss, line);
    if (withNL) line += '\n';
    return true;
}
bool Liner::isEmpty()
{
    return ss.eof();
}
void Liner::skipLines(size_t num)
{
    std::string line;
    for (size_t i = 0; i < num; i++)
        getLine(line);
}


