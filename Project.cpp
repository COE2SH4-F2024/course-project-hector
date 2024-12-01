#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* gamemechs = nullptr;
Player* player = nullptr;
Food* food = nullptr;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(!gamemechs->getExitFlagStatus())  //now uses gamemechs object to check the exit flag (very cool)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gamemechs = new GameMechs();
    player = new Player(gamemechs);
    food = new Food();

    //access head position of snake
    objPosArrayList* playerPosList = player->getPlayerPos();
    objPos headPos = playerPosList->getHeadElement();

    
    food->generateFood(headPos);
}

void GetInput(void)
{
    if(MacUILib_hasChar()){
        char input = MacUILib_getChar();
        gamemechs->setInput(input);
    }
}

void RunLogic(void)
{
    char input = gamemechs->getInput();

    if(input != 0){
        switch(input){

            case '.':
            gamemechs->setExitTrue();
            break;

            case 'S':       //DEBUG KEY FOR ITERATION 1B, WILL REMOVE JUST TEST SCORE WITH IT
            case 's':
            gamemechs->incrementScore();
            break;

            default:
            //player->movePlayer();
            player->updatePlayerDir();      //only updates player movement as long as the exit key is not pressed 
            break;                        

        }
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    //board dimensions
    int rows = gamemechs->getBoardSizeY(); 
    int columns = gamemechs->getBoardSizeX(); 

    objPosArrayList* snake = player->getPlayerPos(); 
    objPos foodPos = food->getFoodPos(); 

    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            bool isSnake = false;
            char toDraw = ' '; 

            if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
                toDraw = '+'; 
            }
            
            //draws snake body
            else {
                for (int k = 0; k < snake->getSize(); k++) {
                    objPos segment = snake->getElement(k);
                    if (segment.pos->y == i && segment.pos->x == j) {
                        isSnake = true;
                        toDraw = segment.symbol;
                        break;
                    }
                }

                //draw food (only if it's not occupied by snake segment)
                if (!isSnake && foodPos.pos->y == i && foodPos.pos->x == j) {
                    toDraw = foodPos.symbol; 
                }
            }

            MacUILib_printf("%c", toDraw);
        }
        MacUILib_printf("\n");
    }

    //debugging messages, we can remove or keep when needed
    MacUILib_printf("\n\nSCORE: %d", gamemechs->getScore());
    MacUILib_printf("\nLOSE FLAG: %d", gamemechs->getLoseFlagStatus());
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
