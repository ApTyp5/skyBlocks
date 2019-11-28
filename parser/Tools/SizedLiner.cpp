//
// Created by arthur on 27.11.2019.
//

#include "SizedLiner.h"
bool SizedLiner::getLine(std::string &line, bool withNL)
{
    return Liner::getLine(line, withNL);
}

SizedLiner::SizedLiner(const std::string &str)
    : Liner(str)
{}

bool SizedLiner::getLine(std::string &line, size_t maxSize, bool withNL)
{
    if (buff.empty())
        if (!Liner::getLine(buff, true))
            return false;

    if (buff.size() <= maxSize) {
        line = std::move(buff);
        return true;
    }

    line = buff.substr(0, maxSize - withNL);
    buff = buff.substr(maxSize - withNL);

    if (withNL) line += "\n";
    return true;
}
