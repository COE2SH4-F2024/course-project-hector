#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
    private:
        objPos foodPos;

    public:
        Food();
        ~Food();

        void generateFood(objPos blockOff);
        objPos getFoodPos() const;
};

#endif