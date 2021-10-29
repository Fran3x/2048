#ifndef SCENE_H
#define SCENE_H
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
class Scene 
{
protected:
    SDL_Window* window;                 // pointer to the window
    SDL_Renderer* renderer;             //pointer to the renderer
    TTF_Font* Arial;
    SDL_Rect CreateRectangle(int x, int y, int w, int h);
public:
    void GameNameText();
    void DrawScene();
    void DrawYes();

};
#endif
