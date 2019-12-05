#include "Algorithm.h"

void Algorithm::Draw() {
    for (auto block: blocks)
        block->Draw();
}

void Algorithm::Add(Block *block) {
    blocks.push_back(block);
}
