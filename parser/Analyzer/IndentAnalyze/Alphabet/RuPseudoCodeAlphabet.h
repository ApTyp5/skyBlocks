//
// Created by arthur on 07.12.2019.
//

#ifndef RUPSEUDOCODEALPHABET_H
#define RUPSEUDOCODEALPHABET_H

#include "BaseAlphabet.h"

class RuPseudoCodeAlphabet: public BaseAlphabet
{
public:
    RuPseudoCodeAlphabet()
        : BaseAlphabet(
        "если",
        "иначе",
        "пока",
        "вызов",
        "функция",
        {' ', '\t'},
        {';'})
    {}
};
#endif //RUPSEUDOCODEALPHABET_H
