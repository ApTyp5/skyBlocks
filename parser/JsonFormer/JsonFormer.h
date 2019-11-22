//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_JSONFORMER_JSONFORMER_H_
#define PARSER_JSONFORMER_JSONFORMER_H_

#include <string>

typedef jsonString std::string;

class JsonFormer {
 public:
  void addAloneProperty(std::string path, std::string name);
  void addGroupProperty(std::string path, std::string name);
  jsonString
};

#endif //PARSER_JSONFORMER_JSONFORMER_H_
