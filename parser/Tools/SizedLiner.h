//
// Created by arthur on 27.11.2019.
//

#ifndef SIZEDLINER_H
#define SIZEDLINER_H

#include "Liner.h"

class SizedLiner: public Liner
{
public:
    explicit SizedLiner(const std::string &str);
public:
    bool getLine(std::string &line, bool withNL = true) override;
    bool getLine(std::string &line, size_t maxSize, bool withNL = true);
private:
    std::string buff;
};


#endif //SIZEDLINER_H
