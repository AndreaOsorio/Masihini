#include <stdio.h>
#include <map>
#include <iostream>
#include "../Semantics/Type.hpp"
using namespace std;

template <class T>
class MemoryDispatcher{
    private:
    int memLowerLimit = 0;
    int memUpperLimit = 0;
    int memCounter = 0;

    void copyMemory(MemoryDispatcher *memDispatcher){

       auto temp_mem = memDispatcher->mem;
        typedef typename std::map<int,T>::const_iterator It;
            for (It p = temp_mem.begin(); p!=temp_mem.end(); ++p) 
            mem[p->first] = p->second;
    }



    public:
    //Memory map
    map<int,T> mem;

    MemoryDispatcher(int lowerLimit, int frameSize){
        
        memLowerLimit = lowerLimit;
        memUpperLimit = lowerLimit + frameSize;
        memCounter = memLowerLimit;

    }

    MemoryDispatcher(MemoryDispatcher *memDispatcher){
        copyMemory(memDispatcher);
    }

    void dumpMemory(){
        typedef typename std::map<int,T>::const_iterator It;
            for (It p = mem.begin(); p!=mem.end(); ++p) 
            cout<<p->first<<"--->"<<p->second<<endl;

    }
    
    template <class X>
    int insert(X value){
        mem[memCounter] = value;
        int memDir = memCounter;
        memCounter++;

        if (memCounter > memUpperLimit){
            triggerOutOfMemoryError();
        }

        return memDir;
    }

    void setValue(int memDir, T value){
        mem[memDir] = value;
    }

    template <class Y>
    Y getValue(int memDir){
        return mem[memDir];
    }


    void triggerOutOfMemoryError(){
        cout<<"System out of memory"<<endl;
        exit(0);
    }

    ~MemoryDispatcher(){
        
    }


};


