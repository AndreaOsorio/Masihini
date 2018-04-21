#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class ArrayInfo{

private:

    int k;
    int sum = 0;
    int r = 1;
    vector<int> dimensions;
    vector<int> mDimensions;

    bool isArrayEnd = false;
    int numDimensions;
    int mDim;

public:

    ArrayInfo(int limDim){
        calculateR(limDim);
    }
    
    int getMDim(int pos){
        return mDimensions.at(pos);
    }

private:

    void calculateR(int lim)
    {
        dimensions.push_back(lim + 1);
        r *= (lim + 1);

        if(isArrayEnd)
        {
            mDim = r;
            numDimensions = dimensions.size();
            calculateMdim(0);
        }
    }

    void calculateK(int n)
    {
        sum = sum * mDimensions.at(n);
    }

    void calculateMdim(int n)
    {
        int aux = mDim / dimensions.at(n);
        mDimensions.push_back(aux);
        mDim = aux;
        calculateK(n);
        for(int i = 1; i < numDimensions; i++)
        {
            calculateMdim(n+1);
            calculateK(n+1);
        }
        
    }


    void setEnd()
    {
        isArrayEnd = true;
    }

    int getK()
    {
        return k;
    }



};
