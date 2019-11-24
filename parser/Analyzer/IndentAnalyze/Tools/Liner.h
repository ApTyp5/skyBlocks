//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_TOOLS_LINER_H_
#define PARSER_ANALYZER_INDENTANALYZE_TOOLS_LINER_H_

#include <sstream>
#include <string>

class Liner
{
public:
    explicit Liner(const std::string &text);

    bool getLine(std::string &line);

private:
    std::stringstream ss;
};

#endif //PARSER_ANALYZER_INDENTANALYZE_TOOLS_LINER_H_
