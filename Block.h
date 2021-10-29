#ifndef BLOCK_H
#define BLOCK_H

#include <array>
#include "SDL_ttf.h"

class Block {
    private:
        int value;
        int r;
        int g;
        int b;
    public:
        Block();
        Block(int number);
        void AssignColor();
        int GetR();
        int GetG();
        int GetB();
        int GetValue();
};

#endif