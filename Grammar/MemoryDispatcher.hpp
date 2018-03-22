

#pragma once
#include <stdio.h>
#include <map>

using namespace std;

template <class T>
class MemoryDispatcher{
    private:

    map<int,T> mem;
    int memLowerLimit = 0;
    int memUpperLimit = 0;
    int memCounter = 0;

    
    
    public:
    MemoryDispatcher(int lowerLimit, int frameSize){
        
        memLowerLimit = lowerLimit;
        memUpperLimit = lowerLimit + frameSize;
        memCounter = memLowerLimit;

    }
    
    int insert(T value){
        mem[memCounter] = value;
        int memDir = memCounter;
        memCounter++;

        return memDir;
    }

    int declare(T value){
        mem[memCounter] = value;
        int memDir = memCounter;
        memCounter++;
        return memDir;
    }

    T getValue(int memDir){
        return mem[memDir];
    }

    ~MemoryDispatcher(){
        
    }

};


