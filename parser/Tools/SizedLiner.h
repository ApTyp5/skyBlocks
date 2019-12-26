//
// Created by arthur on 27.11.2019.
//

#ifndef SIZEDLINER_H
#define SIZEDLINER_H

#include "Liner.h"

class SizedLiner: public Liner
{
public:
    explicit SizedLiner(const std::wstring &str);
public:
    bool getLine(std::wstring &line, bool withNL = true) override;
    bool getLine(std::wstring &line, size_t maxSize, bool withNL = true);
private:
    std::wstring buff;
};


#endif //SIZEDLINER_H
