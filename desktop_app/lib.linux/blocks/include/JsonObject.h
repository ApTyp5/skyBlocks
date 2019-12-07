#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "Figure.h"
#include <string>

const std::string typeField = "type";
const std::string centerPositionField = "center";
const std::string rectSizesField = "size";
const std::string textField = "text";
const std::string pageField = "page";

const std::string widthField = "width";
const std::string heightField = "height";

const std::string X = "x";
const std::string Y = "y";

const std::string beginField = "begin";
const std::string endField = "end";

const std::string lineType = "line";
const std::string blockType = "follow";
const std::string funcType = "innerblock";
const std::string ifType = "fork";
const std::string whileBeginType = "begincycle";
const std::string whileEndType = "endcycle";


class JsonObject {
public:
    virtual ~JsonObject() = default;

    virtual bool IsArray() const = 0;
    virtual bool CheckCorrect() const = 0;

    virtual int Count() const = 0;

    virtual FigureData *GetFigure(int num) const = 0;
};

#endif // JSONOBJECT_H
