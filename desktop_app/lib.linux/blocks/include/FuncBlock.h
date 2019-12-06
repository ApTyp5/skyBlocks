#ifndef DESKTOP_APP_FUNCBLOCK_H
#define DESKTOP_APP_FUNCBLOCK_H

#include "Block.h"

class FuncBlock : public Block {
public:
    FuncBlock() {}
    ~FuncBlock() override {}

    DrawData * Draw() override { return nullptr; }
};

#endif //DESKTOP_APP_FUNCBLOCK_H
