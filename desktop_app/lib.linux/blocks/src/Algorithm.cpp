#include "Algorithm.h"

void Algorithm::Draw() {
    for (int i = 0; i < blocks.size(); i++)
        blocks[i]->Draw();
}

void Algorithm::Add(Block *block) {
    blocks.push_back(block);
}