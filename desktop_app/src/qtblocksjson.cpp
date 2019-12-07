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
    QString temp_str;
    bool ok = true;
    QJsonValue type = jsonValue[typeField.c_str()];
    if (type == QJsonValue::Undefined)
        return false;
    if (!type.isString())
        return false;

    if (type == "line") {
        QJsonValue beginPos = jsonValue[beginField.c_str()];
        if (beginPos == QJsonValue::Undefined)
            return false;

        temp_str = beginPos[X.c_str()].toString();
        temp_str.toDouble(&ok);
        if (!ok)
            return false;

        temp_str = beginPos[Y.c_str()].toString();
        temp_str.toDouble(&ok);
        if (!ok)
            return false;

        QJsonValue endPos = jsonValue[endField.c_str()];
        if (endPos == QJsonValue::Undefined)
            return false;

        temp_str = endPos[X.c_str()].toString();
        temp_str.toDouble(&ok);
        if (!ok)
            return false;

        temp_str = endPos[Y.c_str()].toString();
        temp_str.toDouble(&ok);
        if (!ok)
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

    temp_str = centerPos[X.c_str()].toString();
    temp_str.toDouble(&ok);
    if (!ok)
        return false;

    temp_str = centerPos[Y.c_str()].toString();
    temp_str.toDouble(&ok);
    if (!ok)
        return false;

    QJsonValue rectSizes = jsonValue[rectSizesField.c_str()];
    if (rectSizes == QJsonValue::Undefined)
        return false;

    temp_str = rectSizes[widthField.c_str()].toString();
    temp_str.toDouble(&ok);
    if (!ok)
        return false;

    temp_str = rectSizes[heightField.c_str()].toString();
    temp_str.toDouble(&ok);
    if (!ok)
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
        lineData->beginX = value[beginField.c_str()][X.c_str()].toString().toDouble();
        lineData->beginY = value[beginField.c_str()][Y.c_str()].toString().toDouble();
        lineData->endX = value[endField.c_str()][X.c_str()].toString().toDouble();
        lineData->endY = value[endField.c_str()][Y.c_str()].toString().toDouble();

        return lineData;
    }

    auto blockData = new BlockData;

    if (type == blockType)
        blockData->figureType = BLOCK;
    else if (type == funcType)
        blockData->figureType = FUNC;
    else if (type == ifType)
        blockData->figureType = IF;
    else if (type == whileBeginType)
        blockData->figureType = WHILEBEGIN;
    else if (type == whileEndType)
        blockData->figureType = WHILEEND;

    blockData->centerPosX = value[centerPositionField.c_str()][X.c_str()].toString().toDouble();
    blockData->centerPosY = value[centerPositionField.c_str()][Y.c_str()].toString().toDouble();
    blockData->rectangleWidth = value[rectSizesField.c_str()][widthField.c_str()].toString().toDouble();
    blockData->rectangleHeight = value[rectSizesField.c_str()][heightField.c_str()].toString().toDouble();
    blockData->innerText = value[textField.c_str()].toString().toStdString();

    return blockData;
}

