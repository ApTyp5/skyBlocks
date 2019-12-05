//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ERROR_ERROR_H_
#define PARSER_ERROR_ERROR_H_

#include <string>
#include <exception>

class Error
{
    int row, col;
    std::string message;

public:
    explicit Error(std::string message = "", int row = -1, int col = -1)
        :
        message(std::move(message)), row(row), col(col)
    {}

    bool operator==(const Error &e) const
    {
        return (row == e.row) && (col == e.col) && (message == e.message);
    }

    bool operator!=(const Error &e) const
    { return !operator==(e); }
};

#endif //PARSER_ERROR_ERROR_H_
