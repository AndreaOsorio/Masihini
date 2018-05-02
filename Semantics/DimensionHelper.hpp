#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

/**
 * This class contains the Dimension helper.
 * It manages the information from the current called array.
 */

class DimensionHelper{

private:

    string identifier;
    int memoryDirection;
    int currentDimension;
    vector<int> dimensionInformation;

public:

    DimensionHelper(string id, int memDir, int currentDim, vector<int> dimInfo){
        identifier = id;
        memoryDirection = memDir;
        currentDimension = currentDim;
        dimensionInformation = dimInfo;
    }

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

    vector<int> getDimInfo(){
        return dimensionInformation;
    }
    

};