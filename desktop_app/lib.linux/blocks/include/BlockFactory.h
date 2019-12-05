#ifndef DESKTOP_APP_BLOCKFACTORY_H
#define DESKTOP_APP_BLOCKFACTORY_H

#include "Algorithm.h"
#include "Block.h"
#include "JsonObject.h"

enum BlockTypes {
    FUNCBLOCK = 0,
    IFBLOCK,
    IOBLOCK,
};

class BlockFactory {
public:
    BlockFactory() = default;
    ~BlockFactory() = default;

    Block *CreateBlock(BlockData *blockData);
    Algorithm *CreateAlgorithm(const JsonObject &json);
};

#endif //DESKTOP_APP_BLOCKFACTORY_H
