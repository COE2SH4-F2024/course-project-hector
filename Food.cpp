#include "Food.h"
#include "GameMechs.h"

Food::Food()
{
    foodPos.pos->x = 0;
    foodPos.pos->y = 0;
    foodPos.symbol = 0;

}

Food::~Food()
{
    delete foodPos.pos;
}

void Food::generateFood(objPos blockOff)
{
    int newX;
    int newY;
    char newSym;
    int notFound = 1;
    int invalidChar = 1;
    int newChar;
    srand(time(NULL));

    while(notFound)
    { 
        // rand() % (max - min + 1) + min;          where [min, max]
        newX = rand() % (30 - 1 + 1) + 1;
        newY = rand() % (15 - 1 + 1) + 1;
        newSym = rand() % (126 - 33 + 1) + 33;

        notFound = (newX == blockOff.pos -> x || newY == blockOff.pos -> y || newSym == blockOff.symbol);
            
        
    }
    foodPos.pos->x = newX;
    foodPos.pos->y = newY;
    foodPos.symbol = newSym;

}

objPos Food::getFoodPos() const
{
    return foodPos;
}