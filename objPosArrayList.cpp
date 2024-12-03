#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP; 
}

objPosArrayList::objPosArrayList(int size)
{
    aList = new objPos[size];
    listSize = 5;
    arrayCapacity = 5; 
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //need to shift elements before.
    int i;

    if(listSize >= arrayCapacity){
        return;
    }
    else{
        for(i = listSize; i > 0; i--){
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
        listSize++;

    }
}

void objPosArrayList::insertTail(objPos thisPos)
{    
    if(listSize >= arrayCapacity){  // list reached its capacity!
        return;
    }
    else
    {
        aList[listSize] = thisPos;  // set to last element
        listSize++;                 // increase size of list
    }
}

void objPosArrayList::removeHead()
{
    int i;
    if(listSize == 0){  // cannot remove from an empty list
        return;
    }
    else
    {
        for(i = 0; i < listSize - 1; i++){
            aList[i] = aList[i+1];  // shift the second element to the head position
        }
        listSize--; // decrease size of list
    }
}

void objPosArrayList::removeTail()
{
    if(listSize == 0){      // cannot remove from an empty list
        return;
    }
    else{
        listSize--;         // decrease size of list
    }
    
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
    
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if(index >= arrayCapacity){             // index surpasees the array capacity!
        return aList[arrayCapacity- 1];     // return the last element of the array instead
    }

    if(index < 0){          // index is too small!
        return aList[0];    // return first element instead
    }

    return aList[index];    // return the objPos element at parameterized index
}




