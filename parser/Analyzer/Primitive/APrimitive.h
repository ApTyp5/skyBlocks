//
// Created by arthur on 22.11.2019.
//

#ifndef PARSER_PRIMITIVE_APRIMITIVE_H_
#define PARSER_PRIMITIVE_APRIMITIVE_H_

#include <string>

#include "../../Scheduler/AScheduler.h"
#include "../../Tools/Liner.h"

class APrimitive {
 public:
  explicit APrimitive(std::string text)
      : innerText(std::move(text)) {}

  virtual ~APrimitive() = default;

  virtual bool acceptScheduler(AScheduler &scheduler) const = 0;

  virtual size_t maxTextWid() const = 0;

  size_t getMaxTextWid(const std::string &str) const {
    Liner liner(str);
    std::string line;
    size_t maxWid = 0;

    while (liner.getLine(line, false))
      if (line.size() > maxWid)
        maxWid = line.size();

    return maxWid;
  }

  size_t getLineNum(const std::string &str) const {
    Liner liner(str);
    std::string line;
    size_t result = 0;

    while (liner.getLine(line)) {
      result++;
    }
    return result;
  }

  virtual bool hasChildren() const {
    return false;
  }

  virtual std::string toString() const {
    return std::string("innerText:") + innerText + "\n";
  }

 protected:
  std::string innerText;

 public:
  const std::string &getInnerText() const {
    return innerText;
  }
};
#endif //PARSER_PRIMITIVE_APRIMITIVE_H_
