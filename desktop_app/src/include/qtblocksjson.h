#ifndef QTBLOCKSJSON_H
#define QTBLOCKSJSON_H

#include "JsonObject.h"
#include <QJsonValue>

class QtBlocksJson : public JsonObject {
public:
    explicit QtBlocksJson(QJsonValue obj): object(obj) {}
    ~QtBlocksJson() override {}

    bool IsArray() const override;
    bool CheckCorrect() const override;

    bool CheckCorrect(const QJsonValue &jsonValue) const;

    int Count() const override;

    BlockData *GetBlock(int num) const override;
private:
    QJsonValue object;
};

#endif // QTBLOCKSJSON_H
