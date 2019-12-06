#ifndef DESKTOP_APP_IOBLOCK_H
#define DESKTOP_APP_IOBLOCK_H

#include "Block.h"

class WhileBlock : public Block {
public:
    ~WhileBlock() override {}

    DrawData * Draw() override { return nullptr; }
};

#endif //DESKTOP_APP_IOBLOCK_H
