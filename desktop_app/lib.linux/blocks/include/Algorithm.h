#ifndef DESKTOP_APP_ALGORITHM_H
#define DESKTOP_APP_ALGORITHM_H

#include "Block.h"
#include "vector"

class Algorithm : public Block {
public:
    Algorithm() = default;
    ~Algorithm() override {
        for (auto block : blocks)
            delete(block);
    }

    void Draw() override;
    void Add(Block *block);

private:
    std::vector<Block *> blocks;
};

#endif //DESKTOP_APP_ALGORITHM_H
