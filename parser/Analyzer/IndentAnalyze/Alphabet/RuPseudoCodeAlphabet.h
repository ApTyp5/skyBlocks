//
// Created by arthur on 07.12.2019.
//

#ifndef RUPSEUDOCODEALPHABET_H
#define RUPSEUDOCODEALPHABET_H

#include "BaseIndentAlphabet.h"

class RuPseudoCodeAlphabet: public BaseIndentAlphabet
{
public:
    RuPseudoCodeAlphabet()
        : BaseIndentAlphabet(
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
