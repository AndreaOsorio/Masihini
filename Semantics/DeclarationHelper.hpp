#pragma once
#include <iostream>
#include <string>
#include "./Type.hpp"
#include "./FuncDir.hpp"
#include "./varTable.hpp"
#include "../Memory/MemoryFrame.hpp"
#include "../ErrorHandler/CompilationErrorHandler.hpp"
#include "./Dimension.hpp"

using namespace std;

class DeclarationHelper{

private:

    //Configuration for Global Frames
    int globalMemoryOffset = 25000;
    int localMemoryFrameSize = 10000;

    //Structures that
    DeclarationState declarationState = GLOBAL_;
    Type currentDeclaredType = VOID_;
    FuncNode *currentDeclaredFunction ;
    VarTable *globalSymbolTable;
    FuncDir *functionDirectory ;
    MemoryFrame *globalMemoryFrame;
    CompilationErrorHandler* errorHandler;

    Dimension dimensionInformation;

    DeclarationState  dimensionalDeclarationState = UNIDIMENSIONAL_;
    
public:


    DeclarationHelper(VarTable* varTable, FuncDir* funcDir, MemoryFrame* frame){
        globalSymbolTable = varTable;
        functionDirectory = funcDir;
        globalMemoryFrame = frame;
    }

    //Functions that handle multidimensional variable declaration
    void switchDimensionalDeclarationState(){
        if (dimensionalDeclarationState == UNIDIMENSIONAL_){
            dimensionalDeclarationState = MULTIDIMENSIONAL_;
        }else{
            dimensionalDeclarationState = UNIDIMENSIONAL_;
        }
    }

    //Variable Declaration

    void performVariableDeclaration(string id, bool isParam){
        if(getDeclarationState() == GLOBAL_){

            int memDir = 0;
            bool result = false;

            if(dimensionInformation.isDimensionsEmpty()){
                memDir = globalMemoryFrame->declareValue(getCurrentDeclaredType());
                result = globalSymbolTable->insertNode(new VarNode(id, getCurrentDeclaredType(), memDir)); 
            }
            else{
                memDir = globalMemoryFrame->declareArray(getCurrentDeclaredType(), dimensionInformation.getR());
                result = globalSymbolTable->insertNode(new VarNode(id, getCurrentDeclaredType(), memDir, dimensionInformation));
            }

            if(!result) errorHandler->callForError(GLOBAL_REDEFINITION, id);


        }else{

            MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
            VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
            int memDir = 0;
            bool resultLocal = false;

            if(dimensionInformation.isDimensionsEmpty()){
                memDir = frame->declareValue(getCurrentDeclaredType());
                resultLocal = symbolTable->insertNode(new VarNode(id, getCurrentDeclaredType(), memDir));
            }
            else{
                memDir = frame->declareArray(getCurrentDeclaredType(), dimensionInformation.getR());
                resultLocal = symbolTable->insertNode(new VarNode(id, getCurrentDeclaredType(), memDir, dimensionInformation));
            }
            
            if(isParam) currentDeclaredFunction->addParameter(memDir);
            if(!resultLocal){ errorHandler->callForError(LOCAL_REDEFINITION, id);}
            bool resultGlobal = globalSymbolTable->isContained(id, getCurrentDeclaredType());
            if(resultGlobal){ errorHandler->callForError(GLOBAL_REDEFINITION, id);}
        }

        dimensionInformation.clearDimension();
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

    void setDimensionInformation(Dimension dimension){
        dimensionInformation = dimension;
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

    DeclarationState getdimensionalDeclarationState(){
        return dimensionalDeclarationState;    
    }

    
};
