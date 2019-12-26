//
// Created by arthur on 27.11.2019.
//

#include "SizedLiner.h"
bool SizedLiner::getLine(std::wstring &line, bool withNL)
{
    return Liner::getLine(line, withNL);
}

SizedLiner::SizedLiner(const std::wstring &str)
    : Liner(str)
{}

bool SizedLiner::getLine(std::wstring &line, size_t maxSize, bool withNL)
{
    if (buff.empty())
        if (!Liner::getLine(buff, false))
            return false;

    if (buff.size() <= maxSize)
        line = std::move(buff);
    else {
        line = buff.substr(0, maxSize);
        buff = buff.substr(maxSize);
    }

    if (withNL) line.push_back('\n');
    return true;
}
