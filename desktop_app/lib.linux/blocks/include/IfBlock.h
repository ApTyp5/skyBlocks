#ifndef DESKTOP_APP_IFBLOCK_H
#define DESKTOP_APP_IFBLOCK_H

#include "Block.h"

class IfBlock : public Block {
public:
    ~IfBlock() override {}

    DrawData *Draw() override;
};

#endif //DESKTOP_APP_IFBLOCK_H
