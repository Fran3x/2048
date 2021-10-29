#include "Board.h"


Board::Board()
{
    srand(time(NULL));

    brd = {{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};
    AddRandom();
    AddRandom();

}

void Board::Move(MoveDirection move)
{
	switch (move) {
        case MoveDirection::LEFT:
            //std::cout << "LEFT" << std::endl;
            DrawBoard();
            TransformLeft();
            Swipe();
            TransformLeft();
            DrawBoard();
            break;
        case MoveDirection::UP:
            //std::cout << "UP" << std::endl;
            DrawBoard();
            Swipe();
            DrawBoard();
            break;
        case MoveDirection::RIGHT:
            //std::cout << "Right" << std::endl;
            DrawBoard();
            TransformRight();
            Swipe();
            ReverseRight();
            DrawBoard();
            break;
        case MoveDirection::DOWN:
            //std::cout << "DOWN" << std::endl;
            DrawBoard();
            TransformDown();
            Swipe();
            TransformDown();
            DrawBoard();
            break;
        default:
            std::cout << "Invalid Selection\n";
            break;
	}
	//return 0;
	//if cant move return 1 and send info about lose or win 
}

void Board::TransformDown()
{
    std::array<std::array<int, 4>, 4> tmp = brd;
    for (int x = 0; x < brd.size(); x++) {
        for (int y = 0; y < brd.size(); y++) {
            tmp[y][x] = this->brd[(brd.size()-1) - y][x];
        }
    }
    this->brd = tmp;
}

void Board::TransformLeft()
{
    std::array<std::array<int, 4>, 4> tmp = brd;
    for (int i = 0; i < brd.size(); ++i) {
        for (int j = 0; j < brd.size(); ++j)
        {
            tmp[j][i] = brd[i][j];
        }
    }
    this->brd = tmp;
}

void Board::TransformRight()
{
    TransformLeft();
    TransformDown();
}

void Board::ReverseRight()
{
    TransformDown();
    TransformLeft();
}
void Board::Swipe() //previous MoveUp
{
    std::vector<int> vec;
    

    for (int j = 0; j < this->brd[0].size(); j++) {// x 
        vec.clear();
        for (int i = 0; i < this->brd.size(); i++) 
        {
            vec.push_back(brd[i][j]);
        }
        int number_of_zeros = 0;
        for (int q = 0; q < vec.size(); q++)
        { //
            if (vec[q] == 0) {
                vec.erase(vec.begin() + q);
                vec.push_back(0);
                q--;
                number_of_zeros++;
                if (number_of_zeros > vec.size())
                {
                    break;
                }
            }
        }
        for (int update = 0; update < brd.size(); update++) {
            brd[update][j] = vec[update]; //tymczasowo ten temp
        }
        for (int q = 0; q < vec.size(); q++) {
            if (!(q + 1 == vec.size())) {
                if (vec[q] == vec[q + 1]) {
                    vec[q] += vec[q + 1];
                    vec.erase(vec.begin() + q + 1);
                    vec.push_back(0);
                }
            }
            for (int update = 0; update < brd.size(); update++) {
                brd[update][j] = vec[update]; //tymczasowo ten temp
            }
        }
    }
    //this->brd = tmp;
}


void Board::DrawBoard()
{
    for (int y = 0; y < 4; y++)
    {
       std::cout << "+---+---+---+---+" << std::endl << "| ";
        for (int x = 0; x < 4; x++)
        {
            std::cout << this->brd[y][x];
            std::cout << " | ";
        }
        std::cout << std::endl;
    }
   std::cout << "+---+---+---+---+" << std::endl << std::endl;
}

int Board::AddRandom()
{   
    std::vector <int*> zeros; 
    for (int i = 0; i < this->brd.size(); i++) {
        for (int j = 0; j < this->brd.size(); j++) {
            if (brd[i][j] == 0)
            {
                zeros.push_back(&brd[i][j]);
            }
        }
    }
    if (zeros.size() == 0) {
        return 1; //GAME OVER
    }
    else {
        int randomIndex = rand() % zeros.size();     
        *zeros[randomIndex] = rand() % 2 * 2 + 2 ;
        return 0;
    }
}

bool Board::Does2048Exist()
{
    for (int i = 0; i < this->brd.size(); i++) {
        for (int j = 0; j < this->brd.size(); j++) {
            if (brd[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}


std::array<std::array<int, 4>, 4> Board::GetBoardStatus(){
    return brd;
}


int Board::GetScore(){
    int sum = 0;
    for (int i = 0; i < 4; i++){
       for (int j = 0; j < 4; j++){
           sum += brd[i][j];
       }
    }
    return sum;
}


void Board::Clear(){
    brd = {{
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }};
}