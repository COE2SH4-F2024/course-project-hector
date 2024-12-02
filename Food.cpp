#include "Food.h"
#include "GameMechs.h"
#include "time.h"


Food::Food()
{
    foodBucket = new objPosArrayList(5);

}

Food::~Food() 
{
    for (int i = 0; i < foodBucket->getSize(); i++) 
    {
        objPos food = foodBucket->getElement(i);
        delete food.pos; // Free position memory
    }
    delete foodBucket; // Free foodBucket
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int newX;
    int newY;
    int notFound = 1;
    int invalidChar = 1;
    char newSym;
    
    int blockOffSize = blockOff->getSize();

    //deletes whats in foodbucket here
    while (foodBucket->getSize() > 0)
        {
            foodBucket->removeTail();
        }

    for(int i = 0; i<5; i++) // for loop of 5 to iterate through the 5 elements in foodBucket
    {   
        notFound = 1;

        //objPos currentBuck = foodBucket->getElement(i);
        while(notFound)
        { 
            // rand() % (max - min + 1) + min;          where [min, max]
            newX = rand() % (29 - 2 + 1) + 2;  //[TODO: implement mainGameMech->getboard]
            newY = rand() % (14 - 2 + 1) + 2;
            
            //generates new symbol excluding '*'
            do{
                newSym = rand() % (126 - 34 + 1) + 34;
            }while(newSym == '*');

            notFound = 0;

            for(int j = 0; j < blockOffSize; j++)
            {
                objPos current = blockOff->getElement(j);
                if (newX == current.pos -> x && newY == current.pos -> y || newSym == '*')
                {
                    notFound = 1;
                    break;
                }
            }
            
        }
        if(i==0) //first 2 shall be special
        {
            foodBucket->insertHead(objPos(newX,newY,'!')); //special food
        }
        else if(i==1)
        {
            foodBucket->insertHead(objPos(newX,newY,'~')); // special Food
        }
        else
        {
            foodBucket->insertHead(objPos(newX,newY, newSym)); //'&' used to debug rn or else should be newSym
        }
    }
}

objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}
