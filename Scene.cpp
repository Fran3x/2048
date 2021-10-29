#include "Scene.h"

SDL_Rect Scene::CreateRectangle(int x, int y, int w, int h)
{
    SDL_Rect rect; // creates a rect
    rect.x = x; // x
    rect.y = y; // y
    rect.w = w; // width
    rect.h = h; // height
    return rect;
}

void Scene::GameNameText()
{
    // setup color of a font
    SDL_Color font_color = { 255, 255, 255 };  // color of a text

    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(Arial, "2048", font_color); // creates surface

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface); //converts to texture from surface

    SDL_Rect Message_rectangle = CreateRectangle(150, 30, 120, 100); // creates a rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rectangle);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(Message);
}


void Scene::DrawScene()
{
    //sets background color
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 50); //sets background color
    SDL_RenderClear(renderer);


    SDL_Rect background_rect = CreateRectangle(200, 150, 400, 400);

    // sets color of a rectangle
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);

    // renders rectangle
    SDL_RenderFillRect(renderer, &background_rect);

}
