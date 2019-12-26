//
// Created by arthur on 22.11.2019.
//

#include "IndentConstraintor.h"
#include "../../Tools/Liner.h"

bool IndentConstraintor::findMain(size_t &first_index, size_t &back_index, const std::wstring &text)
{
    size_t front, back;
    front = 1;
    Liner liner(text);
    std::wstring line;

    for (front = 1; liner.getLine(line); front++) {
        if (IndentAnalyzerUtils::isInVector(line.front(), AlphaBet->WordDelimiters()))
            continue;
        if (line.substr(0, AlphaBet->DefineFuncWord().size()) == AlphaBet->DefineFuncWord())
            continue;
        break;
    }

    for (back = front + 1; liner.getLine(line); back++) {
        if (line.substr(0, AlphaBet->DefineFuncWord().size()) == AlphaBet->DefineFuncWord())
            break;
    }

    if (back - front <= 1) {
        push_error(L"main algorithm not found", 0, 0);
        return false;
    }

    first_index = front;
    back_index = back;

    return true;
}

std::wstring IndentConstraintor::findFunc(size_t &line_num,
                                          std::wstring text,
                                          std::wstring name,
                                          DataBaseConnection &connection)
{
    return std::wstring();
}
