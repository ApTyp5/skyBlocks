//
// Created by arthur on 22.11.2019.
//

#include "IndentConstraintor.h"
#include "../../Tools/Liner.h"

bool IndentConstraintor::findMain(size_t &first_index, size_t &back_index, const std::string &text)
{
    size_t front, back;
    front = 1;
    Liner liner(text);
    std::string line;

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
        push_error("main algorithm not found", 0, 0);
        return false;
    }

    first_index = front;
    back_index = back;

    return true;
}

std::string IndentConstraintor::findFunc(size_t &line_num,
                                         std::string text,
                                         std::string name,
                                         DataBaseConnection &connection)
{
    return std::string();
}
