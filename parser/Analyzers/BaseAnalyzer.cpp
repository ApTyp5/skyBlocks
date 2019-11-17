//
// Created by arthur on 09.11.2019.
//

#include "BaseAnalyzer.h"
#include "ClikeAnalyzer.h"

Primitives BaseAnalyzer::analyze(std::string text) {
  /*
}
  std::string line;
  bool cont = true;
    Reader reader(text);
     // Нужна построчная итерация по тексту
     while ((line = reader.getLine()) != 0) {
         switch (chunk_.state_) {
             case Follow:
                 followHandler(line);
                 break;
             case If:
                 ifHandler(line);
                 break;
             case While:
                 whileHandler(line);
                 break;
             default:
                 chunk_.buf.append(line);
         }
         */
  Primitives p;
  return p;
}

std::shared_ptr<BaseAnalyzer> BaseAnalyzer::createAnalyzer(AnalyzerType type) {
  switch (type) {
    case CLike: return std::shared_ptr<BaseAnalyzer>(new ClikeAnalyzer);
  }
}
