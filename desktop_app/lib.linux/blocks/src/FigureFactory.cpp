#include "FigureFactory.h"
#include "Line.h"
#include "Block.h"
#include "FuncBlock.h"
#include "IfBlock.h"
#include "WhileBlock.h"

Figure *FigureFactory::CreateFigure(FigureData *figureData) {
    if (figureData->figureType == LINE) {
        auto newLine = new Line;

        LineData *lineData = static_cast<LineData *>(figureData);

        newLine->setBeginX(lineData->beginX);
        newLine->setBeginY(lineData->beginY);
        newLine->setEndX(lineData->endX);
        newLine->setEndY(lineData->endY);

        return newLine;
    }

    if (figureData->figureType > 0) {
        Block *newBlock = nullptr;

        BlockData *blockData = static_cast<BlockData *>(figureData);

        switch(figureData->figureType) {
        case BLOCK:
            newBlock = new Block;
            break;
        case FUNC:
            newBlock = new FuncBlock;
            break;
        case IF:
            newBlock = new IfBlock;
            break;
        case WHILEBEGIN:
            newBlock = new WhileBlock(BEGIN);
            break;
        case WHILEEND:
            newBlock = new WhileBlock(END);
            break;
        default:
            return nullptr;
        }

        newBlock->setPositionX(blockData->centerPosX);
        newBlock->setPositionY(blockData->centerPosY);
        newBlock->setWidth(blockData->rectangleWidth);
        newBlock->setHeight(blockData->rectangleHeight);
        newBlock->setText(blockData->innerText);

        return newBlock;
    }

    return nullptr;
}

Algorithm *FigureFactory::CreateAlgorithm(const JsonObject &json) {
    if (!json.CheckCorrect() || !json.IsArray())
        return nullptr;

    auto algorithm = new Algorithm;
    int arraySize = json.Count();
    for (int i = 0; i < arraySize; i++) {
        auto figureData = json.GetFigure(i);

        auto block = CreateFigure(figureData);
        algorithm->Add(block);

        delete figureData;
    }

    return algorithm;
}
