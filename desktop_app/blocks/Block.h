#ifndef DESKTOP_APP_BLOCK_H
#define DESKTOP_APP_BLOCK_H

class Block {
public:
    virtual ~Block() = default;

    virtual void Draw() = 0;
};

#endif //DESKTOP_APP_BLOCK_H
