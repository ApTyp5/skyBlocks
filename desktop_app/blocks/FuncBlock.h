#ifndef DESKTOP_APP_FUNCBLOCK_H
#define DESKTOP_APP_FUNCBLOCK_H

#include "Block.h"

class FuncBlock : public Block {
public:
    FuncBlock();
    ~FuncBlock();

    void Draw() override;
};

#endif //DESKTOP_APP_FUNCBLOCK_H
