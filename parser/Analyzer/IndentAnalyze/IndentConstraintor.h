//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTCONSTRAINTOR_H_
#define PARSER_ANALYZER_INDENTCONSTRAINTOR_H_

#include "../AConstraintor.h"

class IndentConstraintor : public AConstraintor {
 public:
  std::string &&findMain(std::string text) override;
  std::string &&findFunc(std::string text, std::string name, DataBaseConnection &connection) override;
};

#endif //PARSER_ANALYZER_INDENTCONSTRAINTOR_H_
