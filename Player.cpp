
#include "Player.h"
#include "Food.h"
#include "GameMechs.h"
#include "MacUILib.h"       //DELETE LATER

Player::Player(GameMechs* thisGMRef, Food* thisFRef) //, Food* thisFRef
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFRef;
    
    myDir = STOP;
    playerPosList = new objPosArrayList();
    // more actions to be included
    int startX = mainGameMechsRef-> getBoardSizeX()/2;      //initiliaze player pos at the centre
    int startY = mainGameMechsRef-> getBoardSizeY()/2;
    playerPosList->insertHead(objPos(startX, startY, '*'));
    consumedFoodIndex = 0;
}

Player::~Player()
{
    delete  playerPosList;
}
objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
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
    int x = playerPosList->getHeadElement().pos->x;      //head position of snake
    int y = playerPosList->getHeadElement().pos->y;
    int xMax = mainGameMechsRef->getBoardSizeX();
    int yMax = mainGameMechsRef->getBoardSizeY();
    //movement logic + including wrap around logic
    switch(myDir){
        case UP:
            y--;
            if(y < 1){      //wrap around logic
                y = yMax - 2;
            }
            break;
        
        case DOWN:
            y++;
            if(y > yMax - 2){
                y = 1; 
            }
            break;
        case LEFT:
            x--;
            if(x < 1){
                x = xMax - 2;
            }
            break;
        case RIGHT:
            x++;
            if(x > xMax - 2){
                x = 1;
            }
        break;
        case STOP:
        default:
            break; //no movement happens (during STOP state)
    }


    if(checkFoodConsumption() == true) // if collision
    {
        objPos current = mainFoodRef->getFoodPos()->getElement(consumedFoodIndex);;
        //MacUILib_printf("%c",current.symbol);
        if(current.symbol == '!')//SPECIAL 1)
        {
            for(int l = 0; l<10; l++)
            {
                mainGameMechsRef->incrementScore();
            }
            current.symbol = ' ';
            mainFoodRef->generateFood(playerPosList);

        }
        else if(current.symbol == '~')//SPECIAL 2)
        {
            increasePlayerLength(x,y);
        }
        else
        {
            playerPosList->insertHead(objPos(x, y, '*'));
            playerPosList->insertTail(objPos(x, y, '*'));
            mainFoodRef->generateFood(playerPosList);
            mainGameMechsRef->incrementScore();
            increasePlayerLength(x,y);
        }
    }
    else if(checkSelfCollision() == true)
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
    else
    {
        //inserts the new head position
        playerPosList->insertHead(objPos(x, y, '*'));
        //deletes tail to simulate movement
        playerPosList->removeTail();
    }
    
}
// More methods to be added
bool Player::checkFoodConsumption()
{
    bool consumed = false;
    int playerX = playerPosList->getHeadElement().pos->x;      //head position of snake
    int playerY = playerPosList->getHeadElement().pos->y;


    for(int i = 0; i < mainGameMechsRef->getBoardSizeX(); i++)
    {
        for(int j = 0; j < mainGameMechsRef->getBoardSizeY(); j++)
        {
            for(int k = 0; k<5; k++)
            {
                objPos currentFood = mainFoodRef->getFoodPos()->getElement(k);
                int foodX = currentFood.pos->x;
                int foodY = currentFood.pos->y;
                
                if(playerX == foodX && playerY == foodY) // Collision happened!
                {
                    // send to function to get the character
                    consumed = true;
                    consumedFoodIndex = k;
                    break;
                }
            }
        }
        
    }
    return consumed;
}

bool Player::checkSelfCollision()
{
    bool selfCollision = false;
    int playerX = playerPosList->getHeadElement().pos->x;      //head position of snake
    int playerY = playerPosList->getHeadElement().pos->y;

    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos current = playerPosList->getElement(i);
        if(playerX == current.pos->x && playerY == current.pos->y) // self collision has occured!
        {
            selfCollision = true;
        }
    }
    return selfCollision;
}

void Player::increasePlayerLength(int xPos, int yPos) // updates player length if obtained special food
{
    for(int i = 0; i<10; i++)
    {
        playerPosList->insertTail(objPos(xPos,yPos,'*'));
    }
}
