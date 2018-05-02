#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include "./DeclarationHelper.hpp"
#include "./SemanticRuleSet.hpp"
#include "../Quadruples/Quadruple.hpp"
#include "./Dimension.hpp"
#include "./DimensionHelper.hpp"

using namespace std;

class SemanticValidationHelper{

private:

    DeclarationHelper* helper;
    stack <int> stackOperand;
    stack <Operator> stackOperator;
    stack <DimensionHelper*> stackDimensions;
    stack <int> pendingJumps;
    CompilationErrorHandler* errorHandler;
    SemanticRuleSet* semanticRules;
    vector<Quadruple*>* quadrupleSet;
    int parameterCounter = 0;
    FuncNode* currentCalledFunction;
    Dimension dimensionInformation;


Type getTypeFromContext(int value){

      Type type;
      if (value > 0){

            if(value<helper->getGlobalOffset()){
                  type = helper->getGlobalMemory()->getType(value);

            }else{
                  MemoryFrame *memFrame = helper->getCurrentDeclaredFunction()->getMemoryFrame();
                  type = memFrame->getType(value);
            }

      }else{
            FuncNode* node = helper->getFunctionAt(value * -1);
            type = node->getType();

      }

      if(type == REFERENCE_){
          return getTypeFromReference(value);
      }

      return type;
}

Type getTypeFromReference(int value){

    int content = -1;

    if(value<helper->getGlobalOffset()){
              content = helper->getGlobalMemory()->getReferenceValue(value);

    }else{
            content = helper->getCurrentDeclaredFunction()->getMemoryFrame()->getReferenceValue(value);
    }

    switch(content){
        case 0: return INTEGER_;
        case 1: return FLOAT_;
        case 2: return STRING_;
        case 3: return BOOLEAN_;
    }


}



void performSystemFunction(Operator op, string id){

    MemoryFrame* memFrame = helper->getCurrentDeclaredFunction()->getMemoryFrame();

      int operand;

      if(!stackOperand.empty())
      {
            operand = stackOperand.top();

            stackOperand.pop();
            Type type = getTypeFromContext(operand);

            if(op == SPEAK_){
                  quadrupleSet->push_back(new Quadruple(SPEAK_, 1, operand, 1));
            }

            if(op == ACCEL_){

                  if(semanticRules->isAllowed(type, VOID_, op) == VOID_){
                        errorHandler->callForError(TYPE_MISMATCH, "");
                  }else{
                      quadrupleSet->push_back(new Quadruple(ACCEL_, 1, operand, 1));
                  }
            }

             if(op == ROT_){
                   if(semanticRules->isAllowed(type, VOID_, op) == VOID_){
                        errorHandler->callForError(TYPE_MISMATCH, "");
                  }else{
                      quadrupleSet->push_back(new Quadruple(ROT_, 1, operand, 1));
                  }
            }

            if(op == STOP_ || op == JUMP_)
                  errorHandler->callForError(TYPE_MISMATCH, ""); 

      }else{

            if(op == STOP_){
                  quadrupleSet->push_back(new Quadruple(STOP_, -1, -1, -1));
            }else if(op == JUMP_){
                  quadrupleSet->push_back(new Quadruple(JUMP_, -1, -1, -1));
            }else{
                  errorHandler->callForError(TOO_FEW_PARAMETERS, id);  
            }
     

      }


}

void performSemantics(bool isNot, bool isAssignment){

    MemoryFrame* memFrame = helper->getCurrentDeclaredFunction()->getMemoryFrame();

    
      
    Operator op = stackOperator.top();
    stackOperator.pop();

    int rightOperand = stackOperand.top();
    stackOperand.pop();
    Type rightType = getTypeFromContext(rightOperand);
    
    int leftOperand = 1;
    Type leftType = VOID_;    

      if(!isNot){
            leftOperand = stackOperand.top();
            leftType = getTypeFromContext(leftOperand);
            stackOperand.pop();
      }
    
      Type resultType = semanticRules->isAllowed(rightType,leftType, op);

      if(resultType == VOID_){
            errorHandler->callForError(TYPE_MISMATCH, "");                     
      }else{                        
            
            if(isAssignment){
                quadrupleSet->push_back( new Quadruple(op, rightOperand, -1, leftOperand));
            }else{
                int result = memFrame->declareValue(resultType);
                quadrupleSet->push_back( new Quadruple(op, leftOperand, rightOperand, result));
                stackOperand.push(result);
            }
      }

}




    
    
public:

    SemanticValidationHelper(DeclarationHelper* h, vector<Quadruple*>* quadSet){
        helper = h;
        quadrupleSet = quadSet;
    }

    void pushOperator(Operator op){
        stackOperator.push(op);
    }

    void pushPendingJumps(int value){
        pendingJumps.push(value);
    }

    void manage_var_cte_id(string id){

        VarTable *symbolTable = helper->getCurrentDeclaredFunction()->getSymbolTable();

        int memDir = symbolTable->search(id);
        if(memDir == -1){
            memDir = helper->getGlobalSymbolTable()->search(id);
            if(memDir==-1){
                   errorHandler->callForError(NON_DECLARED_VARIABLE, id);
            }
            else{
                Dimension tempDim = helper->getGlobalSymbolTable()->getDimensionInformation(id);
                if(!tempDim.isDimensionsEmpty()){
                    stackDimensions.push(new DimensionHelper(id, memDir, 0, tempDim.getDimensionSize()));
                }
            }
        }
        else{
            Dimension tempDim = symbolTable->getDimensionInformation(id);
            if(!tempDim.isDimensionsEmpty()){
                stackDimensions.push(new DimensionHelper(id, memDir, 0, tempDim.getDimensionSize()));
            }
        }

        
        stackOperand.push(memDir);
        
    }

    template<class T>
    void manage_var_cte(T value){

        MemoryFrame *memFrame = helper->getCurrentDeclaredFunction()->getMemoryFrame();
        int memDir = memFrame->registerValue(value);
        stackOperand.push(memDir);

    }


    //Sets of functions that validate semantics
    void popFakeBottom(){
        if (stackOperator.top() ==  FAKE_BTTM_){
            stackOperator.pop();
        }
    }

    void pushFakeBottom(){
        stackOperator.push(FAKE_BTTM_);
    }


    void mult_div_semantics(){
        if(!stackOperator.empty() && (stackOperator.top() == MULT_ || stackOperator.top() == DIV_  )){
            performSemantics(false, false);
        }
    }

     void add_subs_semantics(){
        if(!stackOperator.empty() && ( stackOperator.top() == ADD_ || stackOperator.top() == SUBS_ )){
            performSemantics(false,false);
        }
    }

    void relop_semantics(){
        if(!stackOperator.empty() && ( stackOperator.top() == GT_ || stackOperator.top() == LT_ ||stackOperator.top() == LE_ || stackOperator.top() == GE_ || stackOperator.top() == EE_ )){
            performSemantics(false,false);
        }
    }


    void boolean_semantics(){
        if(!stackOperator.empty() && ( stackOperator.top() == AND_ || stackOperator.top() == OR_ )){
            performSemantics(false,false);
        }
    }

    void not_semantics(){
        if(!stackOperator.empty() && ( stackOperator.top() == NOT_)){
            performSemantics(true,false);
        }
    }

    void assignment_semantics(){
        if(!stackOperator.empty() && (stackOperator.top() == EQ_ )){
            performSemantics(false,true);  
        }
    }


//Functionas that manage cycles

    void cycle_semantics(){

        int expressionResult = stackOperand.top();
        Type type = getTypeFromContext(expressionResult);

        if(type == BOOLEAN_){

            stackOperand.pop();
            quadrupleSet->push_back(new Quadruple(GOTOF_,expressionResult, -1, -1));
            pendingJumps.push(quadrupleSet->size()-1);                    
        }else{                        
            errorHandler->callForError(TYPE_MISMATCH,"");
        }
    }

    void close_cycle(){
        int index = pendingJumps.top();
        pendingJumps.pop();
        quadrupleSet->at(index)->setResult(quadrupleSet->size()+1);

        index = pendingJumps.top();
        pendingJumps.pop();
        quadrupleSet->push_back(new Quadruple(GOTO_,-1, -1, index));
    }

    void system_func_semantics(string value){

        if(!value.compare("speak"))
        performSystemFunction(SPEAK_, value);

        if(!value.compare("move"))
        performSystemFunction(ACCEL_, value);

        if(!value.compare("jump"))
        performSystemFunction(JUMP_, value);

        if(!value.compare("rot"))
        performSystemFunction(ROT_, value);

        if(!value.compare("stop"))
        performSystemFunction(STOP_, value);

    }



//Functions that manage function calls

    void initialize_func_call(string id){

        int result = helper->getFunctionDirectory()->search(id);
        if (result == -1){
            string message;
            errorHandler->callForError(NON_DECLARED_FUNCTION, id);
        }else{

            currentCalledFunction = helper->getFunctionAt(result);
            quadrupleSet->push_back(new Quadruple(ERA_,-1, -1, result));
            parameterCounter = 0;

        }

    }

    void param_assignment(){
        int numberOfParameters = currentCalledFunction->getNumberOfParameters();
        string name = currentCalledFunction->getId();
        if(numberOfParameters==0){
                errorHandler->callForError(TOO_MANY_PARAMETERS,name);
        }else{
                if(numberOfParameters==parameterCounter){
                    errorHandler->callForError(TOO_MANY_PARAMETERS,name);
                }else{

                    int result = stackOperand.top();
                    Type resultType = getTypeFromContext(result);
                    stackOperand.pop();

                    Type parameterType = currentCalledFunction->getParameterType(parameterCounter);

                    if(parameterType==resultType){

                        /** Get param dimension information */
                        VarTable *symbolTable = currentCalledFunction->getSymbolTable();
                        int paramDir = currentCalledFunction->getParameterDirAt(parameterCounter);
                        string paramID = symbolTable->getIdFromMemoryContext(paramDir);
                        Dimension paramDimension = symbolTable->getDimensionInformation(paramID);
                        vector<int> paramDimensions = paramDimension.getDimensionSize();

                        if(!stackDimensions.empty() && !stackOperator.empty()){

                            DimensionHelper* dimHelper = stackDimensions.top();
                            vector<int> resultDimensions = dimHelper->getDimInfo();
                            if ( equal (paramDimensions.begin(), paramDimensions.end(), resultDimensions.begin()) ){
                                int memOffset = accumulate (resultDimensions.begin(), resultDimensions.end(), 1, multiplies<int>());
                                quadrupleSet->push_back(new Quadruple(PARAMETER_, memOffset, result, parameterCounter));
                            }else{
                                errorHandler->callForError(ARRAY_PARAMETERS_MISMATCH,name);
                            }
                            stackDimensions.pop();
                        }
                        else{
                            quadrupleSet->push_back(new Quadruple(PARAMETER_, -1, result, parameterCounter));
                        }
                    }else{
                            errorHandler->callForError(TYPE_MISMATCH,"");
                    }
                    parameterCounter++;
                }

        }

    }

    void subscribe_func_call(string id){

        stackOperator.pop();
        int result = helper->getFunctionDirectory()->search(id);
        int numberOfParameters = currentCalledFunction->getNumberOfParameters();
        if (parameterCounter < numberOfParameters ){
            errorHandler->callForError(TOO_FEW_PARAMETERS, id);
        }else{
            quadrupleSet->push_back(new Quadruple(GOSUB_,-1, -1, result)); 
        }

    }

    void func_call_as_exp(){
        int index = quadrupleSet->at(quadrupleSet->size()-1)->getResult() * -1;
        stackOperand.push(index);
    }

    void func_call_pop_result(){
        if(currentCalledFunction->getType() != VOID_ ){
            int index = helper->getFunctionDirectory()->search(currentCalledFunction->getId());
            quadrupleSet->push_back(new Quadruple(POPRES_, 0,0, index));
        }
    }

    //Functions that manage conditionals


    void conditional_semantics(){

        int expressionResult = stackOperand.top();
        Type type = getTypeFromContext(expressionResult);

        if(type == BOOLEAN_){

                stackOperand.pop();
                quadrupleSet->push_back(new Quadruple(GOTOF_,expressionResult, -1, -1));
                pendingJumps.push(quadrupleSet->size()-1);                    
        }else{                        
                errorHandler->callForError(TYPE_MISMATCH, "");
        }
    }

    void perform_else(){

        int index = pendingJumps.top();
        pendingJumps.pop();

        quadrupleSet->at(index)->setResult(quadrupleSet->size()+1);

        quadrupleSet->push_back(new Quadruple(GOTO_,-1, -1, -1));

        pendingJumps.push(quadrupleSet->size()-1);

    }

    void conditional_close(){
        int index = pendingJumps.top();
        pendingJumps.pop();

        quadrupleSet->at(index)->setResult(quadrupleSet->size());
    }

//Functions that handle function return
    void perform_return(){
        int result = stackOperand.top();
        Type resultType = getTypeFromContext(result);
        stackOperand.pop();

        Type functionType = helper->getCurrentDeclaredFunction()->getType();
        int numberOfDimensions = helper->getCurrentDeclaredFunction()->getNumberOfDimensions();
        string id = helper->getCurrentDeclaredFunction()->getId();
        int index = helper->getFunctionDirectory()->search(id);

        /** Get return value dimension information */
        VarTable *symbolTable = helper->getCurrentDeclaredFunction()->getSymbolTable();
        string resultID = symbolTable->getIdFromMemoryContext(result);
        Dimension resultDimension = symbolTable->getDimensionInformation(resultID);
        vector<int> resultDimensions = resultDimension.getDimensionSize();

        if((resultType == functionType) && (resultDimensions.size() == numberOfDimensions) ){
                if(numberOfDimensions > 0){
                    int memOffset = accumulate (resultDimensions.begin(), resultDimensions.end(), 1, multiplies<int>());
                    quadrupleSet->push_back(new Quadruple(RETURN_, memOffset,index, result));
                }
                else{
                    quadrupleSet->push_back(new Quadruple(RETURN_, -1,index, result));
                }            
        }else{
                errorHandler->callForError(TYPE_MISMATCH, "");
        }
    }

    void check_return(){
        Operator operator_ = quadrupleSet->at(quadrupleSet->size()-1)->getOperator();
        Type functionType = helper->getCurrentDeclaredFunction()->getType();

        if(operator_ != RETURN_ && functionType != VOID_){
            string message;
            errorHandler->callForError(RETURN_STATEMENT_MISSING, helper->getCurrentDeclaredFunction()->getId());
        }
        
    }


    //Functions that handle Arrays

    //Functions that handle Array declaration
    void calculateArraySpace(){
        
        MemoryFrame *memFrame = helper->getCurrentDeclaredFunction()->getMemoryFrame();

        int memDir = stackOperand.top();
        int size = memFrame->getIntegerValue(memDir);
        
        dimensionInformation.calculateR(size);
        dimensionInformation.addDimensionSize(size);

        stackOperand.pop();
    }

    Dimension getDimensionDeclarationInfo(){
        return dimensionInformation;
    }

    void clearDimensionDeclarationInformation(){
        dimensionInformation.clearDimension();
    }


    //Functions that handle Array assignment
    void performSemanticsArray(){

        MemoryFrame *memFrame = helper->getCurrentDeclaredFunction()->getMemoryFrame();

        if(!stackDimensions.empty() && !stackOperand.empty()){
            
            //array[index]
            int memDir = stackOperand.top();
            int index = memFrame->getIntegerValue(memDir);

            DimensionHelper* dimHelper = stackDimensions.top();
            int value = dimHelper->getMemDir();
            string id = dimHelper->getId();
            int currentDimension = dimHelper->getCurrentDim();

            Dimension dimInfo;
            if(value < helper->getGlobalOffset()){
                //Global Symbol Table
                dimInfo = helper->getGlobalSymbolTable()->getDimensionInformation(id);
            }else{
                //Local Symbol Table
                VarTable *symbolTable = helper->getCurrentDeclaredFunction()->getSymbolTable();
                dimInfo = symbolTable->getDimensionInformation(id);
            }

            vector<int> dimensions = dimInfo.getDimensionSize();
            int numberOfDimensions = dimensions.size();
            int size = dimensions.at(currentDimension-1);
            
            quadrupleSet->push_back(new Quadruple(VER_, memDir, 0, size));

            //Pointer != NULL
            if(currentDimension < numberOfDimensions){

                int dimM = dimInfo.getR();
                for(int i = 0; i<currentDimension; i++){
                    dimM = dimM/(dimensions.at(currentDimension-1));
                }
                stackOperand.pop();
                int aux = index;                

                Type auxType = getTypeFromContext(memDir);

                if(auxType == INTEGER_ || auxType == REFERENCE_){
                    int tempMemDir = memFrame->declareValue(INTEGER_);
                    int dimMDir = memFrame->registerValue(dimM);

                    quadrupleSet->push_back(new Quadruple(MULT_, memDir, dimMDir, tempMemDir));

                    stackOperand.push(tempMemDir);

                }else{
                    errorHandler->callForError(TYPE_MISMATCH, "");
                }



            }

            //DIM > 1
            if(currentDimension > 1){
                //ultimo temp
                int aux2 = stackOperand.top();
                stackOperand.pop();
                //suma pasada
                int aux1 = stackOperand.top();
                stackOperand.pop();
                

                Type aux2Type = getTypeFromContext(aux2);

                if (aux2Type == INTEGER_ || aux2Type == REFERENCE_){
                    int tempMemDir = memFrame->declareValue(INTEGER_);
                    quadrupleSet->push_back(new Quadruple(ADD_, aux1, aux2, tempMemDir));
                     stackOperand.push(tempMemDir);

                }else{
                     errorHandler->callForError(TYPE_MISMATCH, "");
                     
                }
               
            }

        }
        
    }

    void calculateArrayIndex(){

        MemoryFrame *memFrame = helper->getCurrentDeclaredFunction()->getMemoryFrame();
        if(!stackDimensions.empty() && !stackOperand.empty()){

            DimensionHelper* dimHelper = stackDimensions.top();
            int memDir = dimHelper->getMemDir();
            string id = dimHelper->getId();
            int currentDimension = dimHelper->getCurrentDim();

            Dimension dimInfo;
            
            if(memDir < helper->getGlobalOffset()){
                //Global Symbol Table
                dimInfo = helper->getGlobalSymbolTable()->getDimensionInformation(id);
            }else{
                //Local Symbol Table
                VarTable *symbolTable = helper->getCurrentDeclaredFunction()->getSymbolTable();
                dimInfo = symbolTable->getDimensionInformation(id);
            }
            vector<int> dimensions = dimInfo.getDimensionSize();
            int numberOfDimensions = dimensions.size();


            if( currentDimension == numberOfDimensions ){

                int aux1 = stackOperand.top();
                stackOperand.pop();

                int base = memFrame->registerValue(memDir);

                Type arrayType = getTypeFromContext(memDir);
                int temp = 0;
                
                switch(arrayType){
                    case INTEGER_: temp = memFrame->registerValue(0,0); break;
                    case FLOAT_: temp = memFrame->registerValue(1,0); break;
                    case STRING_: temp = memFrame->registerValue(2,0); break;
                    case BOOLEAN_: temp = memFrame->registerValue(3,0); break;
                }

                quadrupleSet->push_back(new Quadruple(DIR_, aux1, base, temp));

                stackOperand.push(temp);

                //Current array done
                stackDimensions.pop();

            }

        }
        
    }

    int getCurrentDimension(){

        MemoryFrame *memFrame = helper->getCurrentDeclaredFunction()->getMemoryFrame();
        if(!stackDimensions.empty()){

            DimensionHelper* dimHelper = stackDimensions.top();
            int memDir = dimHelper->getMemDir();
            string id = dimHelper->getId();
            int currentDimension = dimHelper->getCurrentDim();

            Dimension dimInfo;
            if(memDir < helper->getGlobalOffset()){
                //Global Symbol Table
                dimInfo = helper->getGlobalSymbolTable()->getDimensionInformation(id);
            }else{
                //Local Symbol Table
                VarTable *symbolTable = helper->getCurrentDeclaredFunction()->getSymbolTable();
                dimInfo = symbolTable->getDimensionInformation(id);
            }
            vector<int> dimensions = dimInfo.getDimensionSize();
            int numberOfDimensions = dimensions.size();

            if( (currentDimension+1) > numberOfDimensions){
                errorHandler->callForError(ARRAY_MISMATCH, "");
            }

            return currentDimension;
        }

        return -1;
    }

    void addNewDimension(int newCurrentDimension){

        if(!stackDimensions.empty()){
            
            DimensionHelper* dimHelper = stackDimensions.top();
            int memDir = dimHelper->getMemDir();
            string id = dimHelper->getId();
            int currentDimension = dimHelper->getCurrentDim();
            
            Dimension dimInfo;
            
            if(memDir < helper->getGlobalOffset()){
                //Global Symbol Table
                dimInfo = helper->getGlobalSymbolTable()->getDimensionInformation(id);
            }else{
                //Local Symbol Table
                VarTable *symbolTable = helper->getCurrentDeclaredFunction()->getSymbolTable();
                dimInfo = symbolTable->getDimensionInformation(id);
            }

            //For Param purposes
            if(currentDimension == 0){
                int expr = stackOperand.top();
                stackOperand.pop();
                stackOperand.pop();
                stackOperand.push(expr); 
            }

            int newExpr = stackOperand.top();
            stackDimensions.pop();
            stackDimensions.push(new DimensionHelper(id, memDir, newCurrentDimension));
            
        }

    }




    

    




    

    
};