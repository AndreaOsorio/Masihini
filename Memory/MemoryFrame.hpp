#pragma once
#include <stdio.h>
#include <map>
#include <string>
#include "MemoryDispatcher.hpp"


using namespace std;

class MemoryFrame{
    private:
    MemoryDispatcher <int>* integerMemoryDispatcher;
    MemoryDispatcher <float>* floatMemoryDispatcher;
    MemoryDispatcher <std::string>* stringMemoryDispatcher;
    MemoryDispatcher <bool>* booleanMemoryDispatcher;
    
    
    public:
        
    int offset;
    int frame;

    MemoryFrame(MemoryFrame *memFrame){
        integerMemoryDispatcher = new MemoryDispatcher<int>(memFrame->getIntegerDispatcher());
        floatMemoryDispatcher = new MemoryDispatcher<float>(memFrame->getFloatDispatcher());
        stringMemoryDispatcher = new MemoryDispatcher<string>(memFrame->getStringDispatcher());
        booleanMemoryDispatcher = new MemoryDispatcher<bool>(memFrame->getBooleanDispatcher());
        this->offset = memFrame->offset;
        this->frame = memFrame->frame;
    }

    MemoryFrame(int offsetValue, int frameSize){

        offset = offsetValue;
        frame = frameSize;

        integerMemoryDispatcher = new MemoryDispatcher<int>(offset,frame); 
        floatMemoryDispatcher = new MemoryDispatcher<float>(offset+frame+1,frame); 
        stringMemoryDispatcher = new MemoryDispatcher<string>(offset+(2*frame)+2,frame);
        booleanMemoryDispatcher = new MemoryDispatcher<bool>(offset+(3*frame)+3,frame);
    }


//Registering values
    int registerValue(int value){
        int res =  integerMemoryDispatcher->insert(value);
        return res;
    }

    int registerValue(float value){
        int res =  floatMemoryDispatcher->insert(value);
        return res;
    }

    int registerValue(string value){
        int res =  stringMemoryDispatcher->insert(value);
        return res;
    }

    int registerValue(bool value){
        int res =  booleanMemoryDispatcher->insert(value);
        return res;
    }


//Declaring values


    int declareValue(Type type){

        switch(type){

            //set default values for a new variable
            case INTEGER_ : return integerMemoryDispatcher->insert(0);
            case FLOAT_ : return floatMemoryDispatcher->insert(0.0f); 
            case STRING_ : return stringMemoryDispatcher->insert("");
            case BOOLEAN_: return booleanMemoryDispatcher->insert(true);
            default : return -1;

        }

    }

//Get type from memory dir

Type getType(int memDir){

    if(memDir >=offset && memDir <= offset+frame) return INTEGER_;
    if(memDir >=(offset+frame+1) && memDir <=(offset+frame+1)+frame) return FLOAT_;
    if(memDir >=(offset+(2*frame)+2) && memDir <=(offset+(2*frame)+2)+frame) return STRING_;
    if(memDir >=(offset+(3*frame)+3,frame) && memDir <=(offset+(3*frame)+3)+frame) return BOOLEAN_;
    
    return VOID_;
}

//Set value from memory direction and value 

    void setValue(int memDir, int value ){
        integerMemoryDispatcher->setValue(memDir,value);
    }

    void setValue(int memDir, float value ){
        floatMemoryDispatcher->setValue(memDir,value);
    }

    void setValue(int memDir, bool value ){
        booleanMemoryDispatcher->setValue(memDir,value);
    }

    void setValue(int memDir, string value ){
        stringMemoryDispatcher->setValue(memDir,value);
    }


//Get value from memory  direction    
    int getIntegerValue(int memDir){
        return integerMemoryDispatcher->getValue(memDir);
    }

    float getFloatValue(int memDir){
        return floatMemoryDispatcher->getValue(memDir);
    }

    string getStringValue(int memDir){
         return stringMemoryDispatcher->getValue(memDir);
    }

    bool getBooleanValue(int memDir){
        return booleanMemoryDispatcher->getValue(memDir);
    }


//Return memoryDispatcher

    MemoryDispatcher <int>* getIntegerDispatcher(){
        return integerMemoryDispatcher;
    }
    MemoryDispatcher <float>* getFloatDispatcher(){
        return floatMemoryDispatcher;
    }
    MemoryDispatcher <string>* getStringDispatcher(){
        return stringMemoryDispatcher;
    }
    MemoryDispatcher <bool>* getBooleanDispatcher(){
        return booleanMemoryDispatcher;
    }



    ~MemoryFrame(){
        
    }

};


