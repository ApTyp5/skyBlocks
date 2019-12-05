#ifndef DESKTOP_APP_IOBLOCK_H
#define DESKTOP_APP_IOBLOCK_H

#include "Block.h"

class IOBlock : public Block {
public:
    IOBlock() {}
    ~IOBlock() {}

    void Draw() override {}
};

#endif //DESKTOP_APP_IOBLOCK_H
