//
// Created by arthur on 07.12.2019.
//

#ifndef INDENTALPHABETCREATOR_H
#define INDENTALPHABETCREATOR_H

#include "BaseIndentAlphabet.h"
#include "../../AlphabetType.h"
#include "RuPseudoCodeAlphabet.h"
#include "PythonLikeAlphabet.h"
class IndentAlphabetCreator
{
public:
    static BaseIndentAlphabet *create(AlphabetType type)
    {
        switch (type) {
            case AlphabetType::RuPseudoCode:return new RuPseudoCodeAlphabet();

            default:
            case AlphabetType::PythonLike:return new PythonLikeAlphabet();
        }
    }
};
#endif //INDENTALPHABETCREATOR_H
