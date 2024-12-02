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

void Food::generateFood(objPosArrayList* blockOff)
{
    int newX;
    int newY;
    int notFound = 1;
    int invalidChar = 1;
    char newSym;
    srand(time(NULL));
    int size = blockOff->getSize();
    for(int i = 0; i < size; i++)
    {
        while(notFound)
        { 
            // rand() % (max - min + 1) + min;          where [min, max]
            newX = rand() % (29 - 2 + 1) + 2;  //[TODO: implement mainGameMech->getboard]
            newY = rand() % (14 - 2 + 1) + 2;
            newSym = rand() % (126 - 34 + 1) + 34;

            objPos current = blockOff->getElement(i);
            notFound = (newX == current.pos -> x || newY == current.pos -> y || newSym == 42);
                
            
        }
        foodPos.pos->x = newX;
        foodPos.pos->y = newY;
        foodPos.symbol = '&';  //!!MAKE SURE TO CHANGE BACK
    }
}

objPos Food::getFoodPos() const
{
    return foodPos;
}