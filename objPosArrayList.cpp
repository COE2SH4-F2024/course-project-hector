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
    if(listSize >= arrayCapacity){
        return;
    }
    else{
        aList[listSize + 1] = thisPos; 
    }
}

void objPosArrayList::removeHead()
{
    int i;

    if(listSize == 0){
        return;
    }
    else{
        for(i = 0; i < listSize - 1; i++){
            aList[i] = aList[i+1];
        }
        listSize--;
    }
}

void objPosArrayList::removeTail()
{
    if(listSize == 0){
        return;
    }
    else{
        listSize--;
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

//char objPosArrayList::getSymbol(int index)
//{
//    return aList[index].symbol;
//}
objPos objPosArrayList::getElement(int index) const
{
    if(index >= arrayCapacity){
        return aList[arrayCapacity- 1];
    }

    if(index < 0){
        return aList[0];
    }

    return aList[index];
}




