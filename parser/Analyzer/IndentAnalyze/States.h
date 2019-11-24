//
// Created by arthur on 23.11.2019.
//

#ifndef PARSER_ANALYZER_INDENTANALYZE_STATES_H_
#define PARSER_ANALYZER_INDENTANALYZE_STATES_H_

enum State {
  Alg,
  UnknownIndent,
  Follow,
  Fork,
  Cycle,
};

#endif //PARSER_ANALYZER_INDENTANALYZE_STATES_H_
