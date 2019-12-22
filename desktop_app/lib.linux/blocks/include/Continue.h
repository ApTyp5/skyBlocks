#ifndef CONTINUE_H
#define CONTINUE_H

#include "Block.h"

class ContinueBlock : public Block {
public:
    ~ContinueBlock() override {}

    DrawData *Draw() override;
};

#endif // CONTINUE_H
