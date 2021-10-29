#include "Visualization.h"

Visualization::Visualization(){
    SDL_Init(SDL_INIT_VIDEO);       // Initialize SDL2

    TTF_Init();

    window = SDL_CreateWindow(
        "2048 game",                // window title
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width,                        // width
        window_height,                       // height
        SDL_WINDOW_OPENGL
    );

    // setup renderer
    renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // setup font
    Arial = TTF_OpenFont("C://Windows//Fonts//Arial.ttf", 24); //  might need absolute font path

    steer = Steering();    // instance of class steering
}

void Visualization::ScoreText()
{    // setup color of a font
    SDL_Color font_color = { 255, 255, 255 };  // color of a text

    // updates score and saves it in variable numb
    int game_score = steer.CurrentBoard().GetScore();

    // concatenate strings
    string wynik = "Wynik: ";
    std::stringstream ss;
    ss << wynik << game_score;
    std::string output = ss.str();

    // string to char[]
    char output_char[12];

    strcpy(output_char, output.c_str());



    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(Arial, output_char, font_color); // creates surface

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface); // converts to texture from surface

    //cover previous score
    SDL_Rect cover;
    cover.w = 200;
    cover.h = 60;;
    cover.x = 450;
    cover.y = 50;

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 50);
    // renders rectangle
    SDL_RenderFillRect(renderer, &cover);



    SDL_Rect Message_rectangle = CreateRectangle(450, 50, 200, 60); //creates a rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rectangle);
    //SDL_RenderDrawRect(renderer, Message, NULL, &Message_rectangle);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(Message);
}

bool Visualization::IsWindowCreated(){
    if (!window) {
        // if window could not be created
        printf("Window could not be created, error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool Visualization::IsRendererCreated(){
    if (!renderer) {
        // if renderer could not be created
        printf("Renderer could not be created, error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool Visualization::IsFontLoaded(){
    if (!Arial) {
        // if arial could not be loaded
        printf("Font could not be loaded, error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}


void Visualization::DrawGrid(){
    //Block blocks[4][4];

    // gets current status of 4x4 board
    std::array<std::array<int, 4>, 4> current_board = steer.CurrentBoard().GetBoardStatus();
    Block current_blocks[4][4];


    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            current_blocks[i][j] = Block(current_board[i][j]);
        }
    }

    SDL_Rect rect;

    for (int i = 0; i < 4; i++){ // width
        for (int j = 0; j < 4; j++){ // height

            rect = CreateRectangle(200 + 16 + i * 96, 150 + 16 + j * 96, 80, 80);


            int r = current_blocks[j][i].GetR();
            int g = current_blocks[j][i].GetG();
            int b = current_blocks[j][i].GetB();

            int num = current_blocks[j][i].GetValue();

            // sets color of a rectangle
            //SDL_SetRenderDrawColor(renderer, 255, 240, 0, 255);
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);

            // renders rectangle
            SDL_RenderFillRect(renderer, &rect);

            if (num != 0){
                DrawNumber(rect.x + 20, rect.y + 20, num);
            }
        }
    }

    // Render the rect to the screen
    SDL_RenderPresent(renderer);
}




void Visualization::DrawNumber(int new_x, int new_y, int numb){
    // setup color of a font
    SDL_Color font_color = {0, 0, 0};  // color of a text

    //int to char[]
    char num_char[16];
    strcpy(num_char, std::to_string(numb).c_str());

    SDL_Surface* surface;
    surface = TTF_RenderText_Solid(Arial, num_char, font_color); // creates surface

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface); //converts to texture from surface

    SDL_Rect Message_rectangle = CreateRectangle(new_x, new_y, 40, 40); //creates a rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rectangle);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(Message);
}

void Visualization::DrawYes()
{
        SDL_Color font_color = { 255, 255, 255 };  // color of a text

        SDL_Surface* surface;
        surface = TTF_RenderText_Solid(Arial, "Yes", font_color); // creates surface

        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface); //converts to texture from surface

        SDL_Rect Message_rectangle = CreateRectangle(360, 480, 80, 50); // creates a rect

        SDL_RenderCopy(renderer, Message, NULL, &Message_rectangle);

        SDL_RenderPresent(renderer);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(Message);
}

Visualization::~Visualization(){
    // Destroy the window
    SDL_DestroyWindow(window);

    // TTF quit
    TTF_Quit();

    // SDL quit
    SDL_Quit();
}

void Visualization::RunTheGame(){
    if (steer.IsNewEvent())
    {
        if (steer.IsQuit())
        {
            // quits the loop
            exit(0);
        }

        steer.HandleKeyboard();  //reads the input and calls functions to change the grid

        if (steer.gameRestart){
            DrawScene();
            DrawGrid();
            ScoreText();
            GameNameText();
            steer.gameRestart = false;
        }

        if (!steer.isGameLost && !steer.isGameWon){
            DrawGrid();
            ScoreText();
        }

        if (steer.isGameLost) {
            GameLostScreen();
            DrawYes();
        }
        if (steer.isGameWon){
            GameWonScreen();
            DrawYes();
        }

    }
}

void Visualization::GameWonScreen(){
    DrawScene();

    // setup color of a font
    SDL_Color font_color = {255, 255, 255};  // color of a text

    //cover board
    SDL_Rect cover = CreateRectangle(200, 150, 400, 400);

    SDL_SetRenderDrawColor(renderer, 50, 50 ,50, 50);
    // renders rectangle
    SDL_RenderFillRect(renderer, &cover);

    SDL_Surface* surface;

    //renders You win text
    surface = TTF_RenderText_Solid(Arial, "You won!", font_color); // creates surface

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface); //converts to texture from surface

    SDL_Rect Message_rectangle = CreateRectangle(200, 50, 400 ,150); // creates a rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rectangle);


    // renders PLAY again
    surface = TTF_RenderText_Solid(Arial, "Play again?", font_color); // creates surface

    Message = SDL_CreateTextureFromSurface(renderer, surface); // converts to texture from surface

    Message_rectangle.y = 250; // y

    SDL_RenderCopy(renderer, Message, NULL, &Message_rectangle);


    // yes button
    SDL_Rect yes_button = CreateRectangle(350, 475, 100, 60); // creates a rect

    //SDL_RenderCopy(renderer, Message, NULL, &yes_button);

    SDL_SetRenderDrawColor(renderer, 0, 176 , 24, 255);
    // renders rectangle
    SDL_RenderFillRect(renderer, &yes_button);


    SDL_FreeSurface(surface);
    SDL_DestroyTexture(Message);

    SDL_RenderPresent(renderer);
}


void Visualization::GameLostScreen(){
    DrawScene();

    // setup color of a font
    SDL_Color font_color = {255, 255, 255};  // color of a text

    //cover board
    SDL_Rect cover = CreateRectangle(200, 150, 400, 400);

    SDL_SetRenderDrawColor(renderer, 50, 50 ,50, 50);
    // renders rectangle
    SDL_RenderFillRect(renderer, &cover);

    SDL_Surface* surface;

    //renders You win text
    surface = TTF_RenderText_Solid(Arial, "You Lost!", font_color); // creates surface

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface); //converts to texture from surface

    SDL_Rect Message_rectangle = CreateRectangle(200, 50, 400, 150); // creates a rect

    SDL_RenderCopy(renderer, Message, NULL, &Message_rectangle);


    //renders PLAY again
    surface = TTF_RenderText_Solid(Arial, "Play again?", font_color); // creates surface

    Message = SDL_CreateTextureFromSurface(renderer, surface); // converts to texture from surface

    Message_rectangle.y = 250; // y

    SDL_RenderCopy(renderer, Message, NULL, &Message_rectangle);


    // yes button
    SDL_Rect yes_button = CreateRectangle(350, 475, 100, 60); // creates a rect

    //SDL_RenderCopy(renderer, Message, NULL, &yes_button);

    SDL_SetRenderDrawColor(renderer, 0, 176 , 24, 255);
    // renders rectangle
    SDL_RenderFillRect(renderer, &yes_button);


    SDL_FreeSurface(surface);
    SDL_DestroyTexture(Message);

    SDL_RenderPresent(renderer);
}

