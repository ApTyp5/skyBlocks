//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ERROR_ERROR_H_
#define PARSER_ERROR_ERROR_H_

#include <string>
#include <exception>
#include "../JsonFormer/JsonFormer.h"

class ParseError: public JsonFormable
{
    int row, col;
    std::wstring message;

public:
    explicit ParseError(std::wstring message, int row = -1, int col = -1)
        :
        message(std::move(message)), row(row), col(col)
    {}

    void acceptJsonFormer(JsonFormer &jFormer) override
    {
        jFormer.addToJson(*this);
    }

    bool operator==(const ParseError &e) const
    {
        return (row == e.row) && (col == e.col) && (message == e.message);
    }

    bool operator!=(const ParseError &e) const
    { return !operator==(e); }

public:
    int getRow() const
    {
        return row;
    }
    int getCol() const
    {
        return col;
    }
    const std::wstring &getMessage() const
    {
        return message;
    }
};

#endif //PARSER_ERROR_ERROR_H_
