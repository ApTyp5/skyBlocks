//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_TOOLS_LINER_H_
#define PARSER_ANALYZER_INDENTANALYZE_TOOLS_LINER_H_

#include <string>
#include <sstream>


class Liner
{
public:
    explicit Liner(const std::wstring &text);

    virtual bool getLine(std::wstring &line, bool withNL = true);
    void skipLines(size_t num);
    bool isEmpty();

private:
    std::wstringstream ss;
};

#endif //PARSER_ANALYZER_INDENTANALYZE_TOOLS_LINER_H_
