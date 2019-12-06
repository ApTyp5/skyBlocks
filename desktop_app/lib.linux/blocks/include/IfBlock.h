#ifndef DESKTOP_APP_IFBLOCK_H
#define DESKTOP_APP_IFBLOCK_H

#include "Block.h"

class IfBlock : public Block {
public:
    ~IfBlock() override {}

    void Draw() override;
};

#endif //DESKTOP_APP_IFBLOCK_H
