#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <time.h>
#include <array>

enum class MoveDirection { UP, LEFT, RIGHT, DOWN };

class Board
{
    private:
        //void TranformUp();
        void TransformDown();
        void TransformLeft();
        void TransformRight();
        void ReverseRight();
        void Swipe();
    public:
        std::array<std::array<int, 4>, 4> brd = { { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}} };
        Board();
        void Move(MoveDirection move);
        void DrawBoard();

        int AddRandom();
        bool Does2048Exist();
        std::array<std::array<int, 4>, 4> GetBoardStatus();
        //void sumValuesOnBoard();    // returns calculated value to board.score
        int GetScore();
        void Clear();
        //~Board()
};

#endif

