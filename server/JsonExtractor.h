//
// Created by arthur on 07.12.2019.
//

#ifndef JSONEXTRACTOR_H
#define JSONEXTRACTOR_H

#include <boost/property_tree/json_parser.hpp>
#include "../parser/Tools/Meta.h"

class JsonExtractor
{
public:
    JsonExtractor(const std::wstring &text)
    {
        std::wistringstream str(text);
        boost::property_tree::read_json(str, tree);
    }

    Meta extractMeta(){
        return {
            tree.get<double>(L"meta.pw"),
            tree.get<double>(L"meta.ph"),
            tree.get<double>(L"meta.xp"),
            tree.get<double>(L"meta.yp"),
            tree.get<double>(L"meta.xm"),
            tree.get<double>(L"meta.ym"),
            tree.get<double>(L"meta.lh"),
            tree.get<double>(L"meta.sw"),
            tree.get<double>(L"meta.bs")
        };
    }

    std::wstring extractText()
    {
        return tree.get<std::wstring>(L"text");
    }

private:
  boost::property_tree::wptree tree;
};


#endif //JSONEXTRACTOR_H
