//
// Created by arthur on 12.11.2019.
//

#ifndef PARSER_ANALYZERS_RUPSEUDOANALYZER_H_
#define PARSER_ANALYZERS_RUPSEUDOANALYZER_H_

#include "AbstractAnalyzer.h"

class RuPseudoAnalyzer: AbstractAnalyzer {
  std::vector<AbstractPrimitive *> analyze(std::string text) override;
};

#endif //PARSER_ANALYZERS_RUPSEUDOANALYZER_H_
