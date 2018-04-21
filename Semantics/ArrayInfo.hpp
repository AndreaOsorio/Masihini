#ifndef ArrayInfo_hpp
#define ArrayInfo_hpp
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class ArrayInfo{

private:

    int dimension = 0;

public:

    ArrayInfo(int dim){
        dimension = dim;
    }
};

#endif
