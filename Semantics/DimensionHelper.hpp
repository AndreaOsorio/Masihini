#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

class DimensionHelper{

private:

    string identifier;
    int memoryDirection;
    int currentDimension;

public:

    DimensionHelper(string id, int memDir, int currentDim){
        identifier = id;
        memoryDirection = memDir;
        currentDimension = currentDim;

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
    

};