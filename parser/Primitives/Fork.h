//
// Created by arthur on 09.11.2019.
//

#ifndef PARSER_PRIMITIVES_FORK_H_
#define PARSER_PRIMITIVES_FORK_H_

#include "AbstractPrimitive.h"

class Fork: public AbstractPrimitive {
 public:
  Fork(std::string text, size_t yesNum, size_t nonum);
 private:
  size_t yesNum, noNum;
};

#endif //PARSER_PRIMITIVES_FORK_H_
