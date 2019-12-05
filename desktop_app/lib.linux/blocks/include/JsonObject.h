#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "Block.h"
#include <string>

const std::string typeField = "type";
const std::string centerPositionField = "center";
const std::string rectSizesField = "rect";
const std::string textField = "text";

class JsonObject {
public:
    virtual ~JsonObject() = default;

    virtual bool IsArray() const = 0;
    virtual bool CheckCorrect() const = 0;

    virtual int Count() const = 0;

    virtual BlockData *GetBlock(int num) const = 0;
};

#endif // JSONOBJECT_H
