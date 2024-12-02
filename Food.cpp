#include "Food.h"
#include "GameMechs.h"
#include "time.h"


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
    int notFound = 1;
    int invalidChar = 1;
    char newSym;
    srand(time(NULL));

    while(notFound)
    { 
        // rand() % (max - min + 1) + min;          where [min, max]
        newX = rand() % (29 - 2 + 1) + 2;  //[TODO: implement mainGameMech->getboard]
        newY = rand() % (14 - 2 + 1) + 2;
        newSym = rand() % (126 - 34 + 1) + 34;

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