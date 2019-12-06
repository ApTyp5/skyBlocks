//
// Created by arthur on 05.12.2019.
//

#include <string>
#include<iostream>
#include "Parser.h"
#include "Analyzer/AnalyzeFactoryType.h"
#include "Analyzer/AnalyzeFactoryCreator.h"
#include "Scheduler/SchedulerCreator.h"


int main()
{
/*    std::string input = "some text, some text\n"
                        "moooore text\n"
                        "\n"
                        "ano block\n"
                        "of\n"
                        "text\n"
                        "\n"
                        "if some condition\n"
                        "   it is multiline condition\n"
                        "\tdo smth useless\n"
                        "else\n"
                        "   while top text;bot text\n"
                        "\t\tinner block\n"
                        "   after while block\n"
                        "after if block\n"
                        "\n"
                        "bye-bye block";*/
    std::string input = "some text, some text\n"
                        "moooore text\n"
                        "\n"
                        "ano block\n"
                        "of\n"
                        "text\n"
                        "\n";

    Meta meta;
    DataBaseConnection db;
    Parser parser(db);
    std::string output = parser.parse(input, AnalyzeFactoryCreator::create(), SchedulerCreator::create(meta));
    std::cout << output;

    return 0;
}