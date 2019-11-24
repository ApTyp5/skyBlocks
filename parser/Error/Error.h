//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ERROR_ERROR_H_
#define PARSER_ERROR_ERROR_H_

#include <string>

struct Error
{
    int row, col;
    std::string message;
    Error(std::string message = "", int row = -1, int col = -1)
        :
        message(std::move(message)), row(row), col(col)
    {}
};

#endif //PARSER_ERROR_ERROR_H_
