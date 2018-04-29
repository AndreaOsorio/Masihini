#ifndef MemoryFrame_hpp
#define MemoryFrame_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <queue>
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

    void dumpMemory(){
        integerMemoryDispatcher->dumpMemory();
        floatMemoryDispatcher->dumpMemory();
        stringMemoryDispatcher->dumpMemory();
        booleanMemoryDispatcher->dumpMemory();
    }


//Registering values

    /** INTEGER */
    int registerValue(int value){
        int res =  integerMemoryDispatcher->insert<int>(value);
        return res;
    }
    
    int registerArr(int value, int memOffset){
        int res =  integerMemoryDispatcher->insertArr<int>(value, memOffset);
        return res;
    }

    /** FLOAT */
    int registerValue(float value){
        int res =  floatMemoryDispatcher->insert<float>(value);
        return res;
    }

    int registerArr(float value, int memOffset){
        int res =  floatMemoryDispatcher->insertArr<float>(value, memOffset);
        return res;
    }

    /** STRING  */
    int registerValue(string value){
        int res =  stringMemoryDispatcher->insert<string>(value);
        return res;
    }

    int registerArr(string value, int memOffset){
        int res =  stringMemoryDispatcher->insertArr<string>(value, memOffset);
        return res;
    }

    /** BOOLEAN */
    int registerValue(bool value){
        int res =  booleanMemoryDispatcher->insert<bool>(value);
        return res;
    }

    int registerArr(bool value, int memOffset){
        int res =  booleanMemoryDispatcher->insertArr<bool>(value, memOffset);
        return res;
    }



//Declaring values


    int declareValue(Type type){

        switch(type){

            //set default values for a new variable
            case INTEGER_ : return integerMemoryDispatcher->insert<int>(0);
            case FLOAT_ : return floatMemoryDispatcher->insert<float>(0.0f); 
            case STRING_ : return stringMemoryDispatcher->insert<string>("");
            case BOOLEAN_: return booleanMemoryDispatcher->insert<bool>(true);
            default : return -1;

        }

    }

    int declareArr(Type type, int memOffset){
        switch(type){

            //set default values for a new variable
            case INTEGER_ : return integerMemoryDispatcher->insertArr<int>(0, memOffset);
            case FLOAT_ : return floatMemoryDispatcher->insertArr<float>(0.0f, memOffset); 
            case STRING_ : return stringMemoryDispatcher->insertArr<string>("", memOffset);
            case BOOLEAN_: return booleanMemoryDispatcher->insertArr<bool>(true, memOffset);
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
        return integerMemoryDispatcher->getValue<int>(memDir);
    }

    float getFloatValue(int memDir){
        return floatMemoryDispatcher->getValue<float>(memDir);
    }

    string getStringValue(int memDir){
         return stringMemoryDispatcher->getValue<string>(memDir);
    }

    bool getBooleanValue(int memDir){
        return booleanMemoryDispatcher->getValue<bool>(memDir);
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

#endif

