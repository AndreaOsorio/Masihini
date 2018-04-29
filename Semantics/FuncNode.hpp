#ifndef FuncNode_hpp
#define FuncNode_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <stack>
#include "./Type.hpp"
#include "./VarTable.hpp"
#include "../Memory/MemoryFrame.hpp"



#endif /* FuncNode_hpp */

using namespace std;

class FuncNode{
private:
    string id;
    Type type;
    int startingInstruction;
    VarTable *symbolTable;
    MemoryFrame *memoryFrame;
    vector<int> parameters;
    stack<int> returnValueStack;
    
    
    
public:
    FuncNode( string identifier, Type dataType, VarTable* symbTable, MemoryFrame* memFrame){
        
        id = identifier;
        type = dataType;
        symbolTable = symbTable;
        memoryFrame = memFrame;
        
    }

    void setReturnValue(int value ){
        returnValueStack.push(value);
    }

    int getReturnValue(){
        
        int returnValue = returnValueStack.top();
        returnValueStack.pop();
        return returnValue;


    }

    void addParameter(int param){
        parameters.push_back(param);
    }

    int getParameterDirAt(int index){
        return parameters.at(index);
    }

    int getNumberOfParameters(){
        return parameters.size();
    }

    Type getParameterType(int index){
        int memDir = parameters.at(index);

        return memoryFrame->getType(memDir);
    }

    string getId() const{
        return id;
    }

    MemoryFrame* getMemoryFrame(){

        return memoryFrame;
    }

    VarTable* getSymbolTable(){
        return symbolTable;
    }

    Type getType(){
        return type;
    }

    int getStartingInstruction(){
        return startingInstruction;
    }

    void setStartingInstruction(int index){
        startingInstruction = index;
    }
    
    
};


namespace std
{
    template<> struct hash<FuncNode>
    {
        size_t
        operator()(const FuncNode & obj) const
        {
            return hash<string>()(obj.getId());
        }
    };
    
}

struct FuncNodeHasher
{
    size_t
    operator()(const FuncNode & obj) const
    {
        return hash<string>()(obj.getId());
    }
};

struct FuncNodeComparator
{
    
    bool
    operator()(const FuncNode & obj1, const FuncNode & obj2) const
    {
        if (obj1.getId() == obj2.getId())
            return true;
        return false;
    }
};