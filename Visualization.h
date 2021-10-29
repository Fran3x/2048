#ifndef VIS_H
#define VIS_H

//#include <bits/stdc++.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Block.h"
#include "Steering.h"
#include "Scene.h"
#include <iostream>
#include <array>
#include <stdio.h>
#include <string>
#include <sstream>


using namespace std;

class Visualization : public Scene {
    protected:
        Steering steer;
  
        int window_width = 800;
        int window_height = 600;
    public:
        Visualization();
        void ScoreText();
        void RunTheGame();

        bool IsWindowCreated();
        bool IsRendererCreated();
        bool IsFontLoaded();

        void DrawGrid();
        void DrawNumber(int new_x, int new_y, int numb);
        void DrawYes();
        void GameWonScreen();
        void GameLostScreen();

        ~Visualization();
};

#endif