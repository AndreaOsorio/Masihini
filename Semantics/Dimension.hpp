#pragma once
#include <stdio.h>
#include <queue>

using namespace std;

class Dimension{

private:

    int numberOfDimensions;
    queue<int> dimensionSize;

public:

    Dimension(int numDim, queue<int> sizes){
        numberOfDimensions = numDim;
        dimensionSize = sizes;
    }

    void setNumberOfDimensions(int number){
        numberOfDimensions = number;
    }

    int getNumberOfDimensions(){
        return numberOfDimensions;
    }

    void addDimensionSize(int newSize){
        dimensionSize.push(newSize);
    }

    queue<int> getDimensionSize(){
        return dimensionSize;
    }


}