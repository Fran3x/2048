#include "Steering.h"


Steering::Steering() {
    this->brd = Board();
    isGameLost = false;
    isGameWon = false;
    gameRestart = false;
}

bool Steering::IsNewEvent(){
    if (SDL_PollEvent(&new_event))
    {
        return true;
    }
    return false;
}

bool Steering::IsQuit(){
    if (new_event.type == SDL_QUIT)
    {
        return true;
    }
    return false;
}

void Steering::HandleKeyboard(){
    bool pressValidator = false;
    if (new_event.type == SDL_KEYDOWN){

        if (!keyPressedNow){
            switch(new_event.key.keysym.sym){
                case SDLK_LEFT:
                    brd.Move(MoveDirection::LEFT);
                    std::cout << "Left\n";
                    pressValidator = true;
                    break;
                case SDLK_UP:
                    brd.Move(MoveDirection::UP);
                    std::cout << "Up\n";
                    pressValidator = true;
                    break;
                case SDLK_RIGHT:
                    brd.Move(MoveDirection::RIGHT);
                    std::cout << "Right\n";
                    pressValidator = true;
                    break;
                case SDLK_DOWN:
                    brd.Move(MoveDirection::DOWN);
                    std::cout << "Down\n";
                    pressValidator = true;
                    break;
                default:
                    pressValidator = false;
            }
            if (pressValidator && brd.AddRandom())
            {
                isGameLost = true;
            }
            else if (pressValidator && brd.Does2048Exist())
            {
                isGameWon = true;
            }
        }

        keyPressedNow = true;
    }

    if (new_event.type == SDL_KEYUP){
        keyPressedNow = false;
    }

    if (new_event.type == SDL_MOUSEBUTTONDOWN && (isGameLost || isGameWon)){
        // gets coordinates of a mouse click
        cout << "MOUSE CLICK";
        int mouse_button_x = new_event.button.x;
        int mouse_button_y = new_event.button.y;
        if (mouse_button_x >= 350 && mouse_button_x < 450 && mouse_button_y >= 475 && mouse_button_y < 535){
            // restart of a game
            brd = Board();
            gameRestart = true;
            isGameLost = false;
            isGameWon = false;
        }
    }
}

Board Steering::CurrentBoard(){
    return brd;
}
