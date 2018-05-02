#pragma once
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;


/**
 * This class contains the Dimension
 * It manages the information from the memory space the array need as well as a vector with the size of each dimension. 
 */

class Dimension{

private:

    int r;
    vector<int> dimensionSize;

public:
    Dimension(){
        r = 1; 
    }

    Dimension(int newR, vector<int> sizes){
        r = newR;
        dimensionSize = sizes;
    }

    void setR(int newR){
        r = newR;
    }

    int getR(){
        return r;
    }

    void calculateR(int newSize){
        r *= newSize;
    }

    void addDimensionSize(int newSize){
        dimensionSize.push_back(newSize);
    }

    vector<int> getDimensionSize(){
        return dimensionSize;
    }

    int getDimensionNumber(){
        return dimensionSize.size();
    }

    bool isDimensionsEmpty(){

        return dimensionSize.empty();
    }

    void clearDimension(){
        r = 1;
        dimensionSize.clear();
    }


};