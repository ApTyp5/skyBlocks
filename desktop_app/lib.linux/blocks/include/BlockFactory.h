#ifndef DESKTOP_APP_BLOCKFACTORY_H
#define DESKTOP_APP_BLOCKFACTORY_H

#include "Block.h"

enum BlockTypes {
    FUNCBLOCK = 0,
    IFBLOCK,
    IOBLOCK,
};

class BlockFactory {
public:
    BlockFactory() = default;
    ~BlockFactory() = default;

    Block *CreateBlock(BlockTypes blockType);
};

#endif //DESKTOP_APP_BLOCKFACTORY_H
