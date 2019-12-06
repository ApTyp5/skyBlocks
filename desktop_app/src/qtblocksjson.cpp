#include "qtblocksjson.h"
#include "Block.h"
#include "Line.h"
#include <QJsonArray>
#include <QString>

bool QtBlocksJson::IsArray() const {
    return object.isArray();
}

bool QtBlocksJson::CheckCorrect() const {
    if (!object.isArray())
        return CheckCorrect(object);

    QJsonArray array = object.toArray();

    for(QJsonValue value : array) {
        if (!CheckCorrect(value))
            return false;
    }

    return true;
}

bool QtBlocksJson::CheckCorrect(const QJsonValue &jsonValue) const {
    QJsonValue type = jsonValue[typeField.c_str()];
    if (type == QJsonValue::Undefined)
        return false;
    if (!type.isString())
        return false;

    if (type == "line") {
        QJsonValue beginPos = jsonValue[beginField.c_str()];
        if (beginPos == QJsonValue::Undefined)
            return false;
        if (!beginPos[X.c_str()].isDouble()
                || !beginPos[Y.c_str()].isDouble())
            return false;

        QJsonValue endPos = jsonValue[endField.c_str()];
        if (endPos == QJsonValue::Undefined)
            return false;
        if (!endPos[X.c_str()].isDouble()
                || !endPos[Y.c_str()].isDouble())
            return false;

        QJsonValue text = jsonValue[textField.c_str()];
        if (text == QJsonValue::Undefined)
            return false;
        if (!text.isString())
            return false;

        return true;
    }

    QJsonValue centerPos = jsonValue[centerPositionField.c_str()];
    if (centerPos == QJsonValue::Undefined)
        return false;
    if (!centerPos[X.c_str()].isDouble() ||
            !centerPos[Y.c_str()].isDouble())
        return false;


    QJsonValue rectSizes = jsonValue[rectSizesField.c_str()];
    if (rectSizes == QJsonValue::Undefined)
        return false;
    if (!rectSizes[widthField.c_str()].isDouble() ||
            !rectSizes[heightField.c_str()].isDouble())
        return false;

    QJsonValue text = jsonValue[textField.c_str()];
    if (text == QJsonValue::Undefined)
        return false;
    if (!text.isString())
        return false;

    return true;
}

int QtBlocksJson::Count() const {
    if (!object.isArray())
        return 0;
    return object.toArray().count();
}

FigureData *QtBlocksJson::GetFigure(int num) const {
    if (!object.isArray())
        return nullptr;

    QJsonArray array = object.toArray();
    if(array.count() <= num)
        return nullptr;

    QJsonValue value = array[num];

    std::string type = value[typeField.c_str()].toString().toStdString();

    if (type == lineType) {
        auto lineData = new LineData;

        lineData->figureType = LINE;
        lineData->beginX = value[beginField.c_str()][X.c_str()].toInt();
        lineData->beginY = value[beginField.c_str()][Y.c_str()].toInt();
        lineData->endX = value[endField.c_str()][X.c_str()].toInt();
        lineData->endY = value[endField.c_str()][Y.c_str()].toInt();

        return lineData;
    }

    auto blockData = new BlockData;

    if (type == blockType)
        blockData->figureType = BLOCK;
    else if (type == ifType)
        blockData->figureType = IF;
    else if (type == whileType)
        blockData->figureType = WHILE;

    blockData->centerPosX = value[centerPositionField.c_str()][X.c_str()].toInt();
    blockData->centerPosY = value[centerPositionField.c_str()][Y.c_str()].toInt();
    blockData->rectangleWidth = value[rectSizesField.c_str()][X.c_str()].toInt();
    blockData->rectangleHeight = value[rectSizesField.c_str()][Y.c_str()].toInt();
    blockData->innerText = value[textField.c_str()].toString().toStdString();

    return blockData;
}

