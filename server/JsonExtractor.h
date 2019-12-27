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
    JsonExtractor(const std::string& text) {
        std::istringstream str(text);
        boost::property_tree::read_json(str, tree);
    }

    Meta extractMeta(){
        return {
            tree.get<double>("meta.pw"),
            tree.get<double>("meta.ph"),
            tree.get<double>("meta.xp"),
            tree.get<double>("meta.yp"),
            tree.get<double>("meta.xm"),
            tree.get<double>("meta.ym"),
            tree.get<double>("meta.lh"),
            tree.get<double>("meta.sw"),
            tree.get<double>("meta.bs")
        };
    }

  std::string extractText() {
    return tree.get<std::string>("text");
  }

  std::string extractLang() {
    return tree.get<std::string>("language");
  }

 private:
  boost::property_tree::ptree tree;
};


#endif //JSONEXTRACTOR_H
