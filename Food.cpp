#include "Food.h"
#include "GameMechs.h"


Food::Food(GameMechs* thisGMRef)
{
    // stores the array of food with set size 5
    foodBucket = new objPosArrayList(5);
    mainGameMechsRef = thisGMRef;
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
        while(notFound) // stay within the for loop until valid element is generated
        { 
            // rand() % (max - min + 1) + min;          where [min, max]
            newX = rand() % ((mainGameMechsRef->getBoardSizeX()-1) - 2 + 1) + 2;    // generate random X and Y values within range
            newY = rand() % ((mainGameMechsRef->getBoardSizeY()-1) - 2 + 1) + 2;
            
            //generates new symbol excluding snake symbol, border symbol or the special characters
            do{
                newSym = rand() % (126 - 34 + 1) + 34;
            }while(newSym == '*' || newSym == '!' || newSym == '~' || newSym == '+');

            notFound = 0; // set to 0

            for(int j = 0; j < blockOffSize; j++)
            {
                objPos current = blockOff->getElement(j);      // get the objPos element of the snake body
                if (newX == current.pos -> x && newY == current.pos -> y || newSym == '*')     // check if randomly generated matches snake body
                {
                    notFound = 1;    // set back to 1 if invalid (invalid food position matches snake)
                    break;
                }
            }
        }
        if(i==0)    // fill first element of foodBucket with special food #1
        {
            foodBucket->insertHead(objPos(newX,newY,'!'));  // adding element to the objPosArrayList
        }
        else if(i==1)
        {
            foodBucket->insertHead(objPos(newX,newY,'~')); // fill second element of foodBucket with special food #2
        }
        else
        {
            foodBucket->insertHead(objPos(newX,newY, newSym));  // the rest of the element symbols will be randomly generated
        }
    }
}

objPosArrayList* Food::getFoodPos() const
{
    return foodBucket;
}
