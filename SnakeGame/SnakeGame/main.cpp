#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>

using namespace std;

//Global variable for game over
//
bool isGameOver;

//consts for map dimensions
//
const int mapWidth = 20;
const int mapLength = 20;

//for head coordinates
//
int x, y;
//fruit coordinates
//
int foodPosX, foodPosY;

int score;

//enum for controller snake
//
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection direction;

//variables foir tail
//
int tailCoorX[100], tailCoordY[100];
int newTail;

//function for setting up map and game
//
void Setup()
{
    isGameOver = false;
    
    //stopped until we start moving the snake
    //
    direction = STOP;
    
    //centering the snake at start
    //
    x = mapWidth / 3;
    y = mapLength / 3;
    
    //positioning the food at a random position
    //
    foodPosX = rand() % mapWidth;
    foodPosY = rand() % mapLength;
    
    score = 0;
}

//drawing our map
//
void Draw()
{
    //clearing the terminal
    //
    system("cls");
    
    //displaying top border
    //
    for (int i = 0; i < mapWidth + 2; i++){
        cout << "=";
    }
    cout << endl;
    
    //printing the map
    //
    for (int i = 0; i < mapLength; i++)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            if(j == 0){
                cout << "=";
            }
            if(i == y && j == x){
                cout << "0";
            }else if(i == foodPosY && j == foodPosX){
                cout << "F";
            }
            else{
                bool print = false;
                for(int k = 0; k < newTail; k++)
                {
                    
                    if(tailCoorX[k] == j && tailCoordY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                    
                }
                if(!print){
                        cout << " ";
                }
                
            }
            
            if (j == mapWidth - 1){
                cout << "=";
            }
            
        }
        cout << endl;
    }
    
    //bottom border
    //
    for (int i = 0; i < mapWidth + 2; i++){
        cout << "=";
    }
    cout << endl;
    cout << "Points: " << score << endl;
}


//handling the controls/keyboard input
//
void Input()
{
    if(_kbhit()){
        switch(_getch())
        {
            case 'a':
                direction = LEFT;
                break;
            case 'd':
                direction = RIGHT;
                break; 
            case 'w':
                direction = UP;
                break;
            case 's':
                direction = DOWN;
                break;
            case 'q':
                isGameOver = true;
                break;
        }
    }
}

void Logic()
{
    int prevX = tailCoorX[0];
    int prevY = tailCoordY[0];
    int prev2X, prev2Y;
    tailCoorX[0] = x;
    tailCoordY[0] = y;
    
    for (int i = 1; i < newTail; i++){
        prev2X = tailCoorX[i];
        prev2Y = tailCoordY[i];
        tailCoorX[i] = prevX;
        tailCoordY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (direction)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    //terminate game if we go out the map
    //
    /*
    if(x > mapWidth || x < 0 || y > mapLength || y < 0)
    {
        isGameOver = true;
    }
    */
    //allows us to go through walls
    //
    if(x >= mapWidth) x = 0; else if (x < 0) x = mapWidth -1;
    if(y >= mapLength) y = 0; else if (y < 0) y = mapLength -1;
    //ending game when we hit our tail
    //
    for(int i = 0; i < newTail; i++){
        if(tailCoorX[i] == x && tailCoordY[i] == y){
            isGameOver = true;
        }
    }
    //enabling us to eat the food
    //
    if(x == foodPosX && y == foodPosY)
    {
        score += 10;
        foodPosX = rand() % mapWidth;
        foodPosY = rand() % mapLength;
        newTail++;
    }
}

int main(){
    
    Setup();
    
    while(!isGameOver)
    {
        Draw();
        Input();
        Logic();
        
        Sleep(15);
    }
    
    return 0;
}
