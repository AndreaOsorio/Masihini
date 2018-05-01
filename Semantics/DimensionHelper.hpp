#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

class DimensionHelper{

private:

    string identifier;
    int memoryDirection;
    int currentDimension;
    int currentExpr;

public:

    DimensionHelper(string id, int memDir, int currentDim, int currentEx){
        identifier = id;
        memoryDirection = memDir;
        currentDimension = currentDim;
        currentExpr = currentEx;

    }

    string getId(){
        return identifier;
    }

    int getMemDir(){
        return memoryDirection;
    }

    int getCurrentDim(){
        return currentDimension;
    }

    int getCurrentExpr(){
        return currentExpr;
    }
    

};