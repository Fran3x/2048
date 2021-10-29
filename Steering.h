#ifndef STEERING_H
#define STEERING_H
#include "SDL.h"
#include <iostream>
//#include <bits/stdc++.h>
#include "Board.h"
#include "SDL.h"
using namespace std;



class Steering{
    //handles events and steering
    private:
        SDL_Event new_event;
        bool keyPressedNow = false;
        Board brd;
    public:
        bool isGameLost;
        bool isGameWon;
        bool gameRestart;

        Steering();
        bool IsNewEvent();
        bool IsQuit();
        void HandleKeyboard();

        Board CurrentBoard();

};

#endif