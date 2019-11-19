#include "BlockFactory.h"
#include "FuncBlock.h"
#include "IfBlock.h"
#include "IOBlock.h"

Block *BlockFactory::CreateBlock(BlockTypes blockType) {
    Block * block = nullptr;
    switch (blockType) {
        case FUNCBLOCK: {
            block = new FuncBlock;
            break;
        }
        case IFBLOCK: {
            block = new IfBlock;
            break;
        }
        case IOBLOCK: {
            block = new IOBlock;
            break;
        }
    }
    return block;
}
