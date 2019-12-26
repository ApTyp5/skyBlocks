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
        L"если",
        L"иначе",
        L"пока",
        L"вызов",
        L"функция",
        {' ', '\t'},
        {';'})
    {}
};
#endif //RUPSEUDOCODEALPHABET_H
