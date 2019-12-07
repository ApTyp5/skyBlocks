#ifndef DESKTOP_APP_IOBLOCK_H
#define DESKTOP_APP_IOBLOCK_H

#include "Block.h"

enum WhileType{
    BEGIN = 0, END
};

class WhileBlock : public Block {
public:
    WhileBlock() : type(BEGIN) {}
    WhileBlock(WhileType wType) : type(wType) {}
    ~WhileBlock() override {}

    void setType(const WhileType &type) { this->type = type; }
    WhileType getType() { return type; }

    DrawData * Draw() override;
private:
    WhileType type;
};

#endif //DESKTOP_APP_IOBLOCK_H
