#pragma once
#include <stdio.h>
#include <queue>

using namespace std;

class Dimension{

private:

    int r;
    queue<int> dimensionSize;

public:
    Dimension(){
        r = 0; 
    }

    Dimension(int newR, queue<int> sizes){
        r = newR;
        dimensionSize = sizes;
    }

    void setR(int newR){
        r = newR;
    }

    int getR(){
        return r;
    }

    void addDimensionSize(int newSize){
        dimensionSize.push(newSize);
    }

    queue<int> getDimensionSize(){
        return dimensionSize;
    }


};