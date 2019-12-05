#include "BlockFactory.h"
#include "FuncBlock.h"
#include "IfBlock.h"
#include "IOBlock.h"

Block *BlockFactory::CreateBlock(BlockData *blockData) {
    Block *block = nullptr;

    int blockType = 0;

    if (blockData->blockType == "follow")
        blockType = FUNCBLOCK;
    else if (blockData->blockType == "fork")
        blockType = IOBLOCK;
    else if (blockData->blockType == "if")
        blockType = IFBLOCK;
    else
        blockType = -1;

    switch(blockType) {
    case FUNCBLOCK:
        block = new FuncBlock;
        break;
    case IFBLOCK:
        block = new IfBlock;
        break;
    case IOBLOCK:
        block = new IOBlock;
        break;
    }

    block->setPositionX(blockData->centerPosX);
    block->setPositionY(blockData->centerPosY);
    block->setWidth(blockData->rectangleWidth);
    block->setHeight(blockData->rectangleHeight);
    block->setText(blockData->innerText);

    return block;
}

Algorithm *BlockFactory::CreateAlgorithm(const JsonObject &json) {
    if (!json.CheckCorrect() || !json.IsArray())
        return nullptr;

    auto algorithm = new Algorithm;
    int arraySize = json.Count();
    for (int i = 0; i < arraySize; i++) {
        auto blockData = json.GetBlock(i);

        auto block = CreateBlock(blockData);
        algorithm->Add(block);

        delete blockData;
    }

    return algorithm;
}
