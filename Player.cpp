#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    int startX = mainGameMechsRef-> getBoardSizeX()/2;      //initiliaze player pos at the centre
    int startY = mainGameMechsRef-> getBoardSizeY()/2;

    playerPos.setObjPos(startX, startY, '*');  
}


Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef-> getInput();
    
    if(input != 0){

        //switch cases for each input given by user
        
        switch(input){

            case 'w':
            case 'W':
                if(myDir != DOWN){
                    myDir = UP;
                }
                break;

            case 's':
            case 'S':
                if(myDir != UP){
                    myDir = DOWN;
                }
                break;

            case 'd':
            case 'D':
                if(myDir != LEFT){
                    myDir = RIGHT;
                }
                break;


            case 'a':
            case 'A':
                if(myDir != RIGHT){
                    myDir = LEFT;
                }
                break;

            default:
                myDir = STOP;
                break;
        }
  
    }      
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    //get current coordinates of player
    int x = playerPos.getObjPos().pos->x;
    int y = playerPos.getObjPos().pos->y;

    //movement logic + includding wrap around logic
    switch(myDir){

        case UP:
            y = (y - 1 + mainGameMechsRef->getBoardSizeY()) % mainGameMechsRef->getBoardSizeY();
            break;
        
        case DOWN:
            y = (y + 1) % mainGameMechsRef->getBoardSizeY();
            break;

        case LEFT:
        x = (x - 1 + mainGameMechsRef->getBoardSizeX()) % mainGameMechsRef->getBoardSizeX();
        break;

        case RIGHT:
        x = (x+1) % mainGameMechsRef->getBoardSizeX();
        break;

        default:
            break; //no movement happens (during STOP state)
    }

    playerPos.setObjPos(x, y, '*');
    
}

// More methods to be added