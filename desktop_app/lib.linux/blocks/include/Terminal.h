#ifndef TERMINAL_H
#define TERMINAL_H

#include "Block.h"

class TerminalBlock : public Block {
public:
    ~TerminalBlock() override {}

    DrawData *Draw() override;
};

#endif // TERMINAL_H
