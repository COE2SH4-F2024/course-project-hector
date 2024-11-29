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

    objPos playerPos =  player->getPlayerPos();
    food->generateFood(playerPos);
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
            player->updatePlayerDir();      //only updates player movement as long as the exit key is not pressed 
            break;                        

        }
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    int i, j;
    int y_max = gamemechs->getBoardSizeY(), x_max = gamemechs->getBoardSizeX();

    objPos foodPos = food->getFoodPos();

    for (i = 0; i < y_max; i++) {
        for (j = 0; j < x_max; j++) {
            if (i == 0 || i == y_max - 1 || j == 0 || j == x_max - 1) {
                MacUILib_printf("+");
            } 
            else if (i == foodPos.pos ->y && j == foodPos.pos->x)
            {
                MacUILib_printf("%c", foodPos.symbol);
            }
            else {
                MacUILib_printf(" "); 
            }
        }

    MacUILib_printf("\n"); 
    }

    //debugging messages from iteration 1B (will delete/keep when needed)
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
