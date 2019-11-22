//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_JSONFORMER_JSONFORMER_H_
#define PARSER_JSONFORMER_JSONFORMER_H_

#include <string>

typedef std::string jsonString;

class JsonFormer {
 public:
  void addAloneProperty(std::string path, std::string name);
  void addGroupProperty(std::string path, std::string name);
  jsonString formJson();
};

#endif //PARSER_JSONFORMER_JSONFORMER_H_
