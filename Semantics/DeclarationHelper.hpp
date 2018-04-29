

#pragma once
#include <iostream>
#include <string>
#include "./Type.hpp"
#include "./FuncDir.hpp"
#include "./varTable.hpp"
#include "../Memory/MemoryFrame.hpp"
#include "../ErrorHandler/CompilationErrorHandler.hpp"

using namespace std;

class DeclarationHelper{

private:

    DeclarationState declarationState = GLOBAL_;
    Type currentDeclaredType = VOID_;
    FuncNode *currentDeclaredFunction ;
    VarTable *globalSymbolTable;
    FuncDir *functionDirectory ;
    MemoryFrame *globalMemoryFrame;
    CompilationErrorHandler* errorHandler;
    int globalMemoryOffset = 25000;
    int localMemoryFrameSize = 10000;
    

    
    
public:


    DeclarationHelper(VarTable* varTable, FuncDir* funcDir, MemoryFrame* frame){
        globalSymbolTable = varTable;
        functionDirectory = funcDir;
        globalMemoryFrame = frame;
    }

    //Variable Declaration

    void performVariableDeclaration(string id, bool isParam){
        if(getDeclarationState() == GLOBAL_){
            int memDir = globalMemoryFrame->declareValue(getCurrentDeclaredType());
            bool result = globalSymbolTable->insertNode(new VarNode(id,getCurrentDeclaredType(), memDir)); 
            if(!result) errorHandler->callForError(GLOBAL_REDEFINITION, id);


        }else{
            MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
            int memDir = frame->declareValue(getCurrentDeclaredType());
            VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
            if(isParam) currentDeclaredFunction->addParameter(memDir);

            bool resultLocal = symbolTable->insertNode(new VarNode(id,getCurrentDeclaredType(), memDir)); 
            if(!resultLocal){ errorHandler->callForError(LOCAL_REDEFINITION, id);}
            bool resultGlobal = globalSymbolTable->isContained(id, getCurrentDeclaredType());
            if(resultGlobal){ errorHandler->callForError(GLOBAL_REDEFINITION, id);}
        }
    }

    //FunctionDeclaration

    void performFunctionDeclaration(string id){

        currentDeclaredFunction = new FuncNode(id, getCurrentDeclaredType(), new VarTable(), new MemoryFrame(globalMemoryOffset, localMemoryFrameSize));
        bool result = functionDirectory->insertNode(currentDeclaredFunction);
        if(!result){ errorHandler->callForError(FUNCTION_REDEFINITION, id);}
       
    }




    //Utility Functions

    void setDeclarationStateToLocal(){
        declarationState = LOCAL_;
    }

    DeclarationState getDeclarationState(){
        return declarationState;
    }

    void setCurrentDeclaredType(Type type){
        currentDeclaredType = type;
    }

    int getGlobalOffset(){
        return globalMemoryOffset;
    }

    FuncDir* getFunctionDirectory(){
        return functionDirectory;
    }

    FuncNode* getFunctionAt(int value){
        return functionDirectory->getFuncList()->at(value);
    }

    MemoryFrame* getGlobalMemory(){
        return globalMemoryFrame;
    }

    VarTable* getGlobalSymbolTable(){
        return globalSymbolTable;
    }

    Type getCurrentDeclaredType (){
        return currentDeclaredType;
    }

    FuncNode* getCurrentDeclaredFunction(){
        return currentDeclaredFunction;
    }




    

    
};



