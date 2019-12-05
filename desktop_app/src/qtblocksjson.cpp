#include "qtblocksjson.h"
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

    QJsonValue centerPos = jsonValue[centerPositionField.c_str()];
    if (centerPos == QJsonValue::Undefined)
        return false;
    if (!centerPos.isArray())
        return false;

    QJsonArray centerArray = centerPos.toArray();
    if (centerArray.count() < 2)
        return false;
    if (!centerArray[0].isDouble() || !centerArray[1].isDouble())
        return false;


    QJsonValue rectSizes = jsonValue[rectSizesField.c_str()];
    if (rectSizes == QJsonValue::Undefined)
        return false;
    if (!rectSizes.isArray())
        return false;

    QJsonArray rectSizesArray = centerPos.toArray();
    if (rectSizesArray.count() < 2)
        return false;
    if (!rectSizesArray[0].isDouble() || !rectSizesArray[1].isDouble())
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

BlockData *QtBlocksJson::GetBlock(int num) const {
    if (!object.isArray())
        return nullptr;
    auto blockData = new BlockData;

    QJsonArray array = object.toArray();
    if(array.count() <= num)
        return nullptr;

    QJsonValue value = array[num];

    blockData->blockType = value[typeField.c_str()].toString().toStdString();
    blockData->centerPosX = value[centerPositionField.c_str()][0].toDouble();
    blockData->centerPosY = value[centerPositionField.c_str()][1].toDouble();
    blockData->rectangleWidth = value[rectSizesField.c_str()][0].toDouble();
    blockData->rectangleHeight = value[rectSizesField.c_str()][1].toDouble();
    blockData->innerText = value[textField.c_str()].toString().toStdString();

    return blockData;
}

