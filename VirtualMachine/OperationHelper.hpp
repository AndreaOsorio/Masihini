#pragma once
#include <stdio.h>
#include <iostream>
#include "../Semantics/Type.hpp"
#include "../Memory/MemoryFrame.hpp"
#include "../Quadruples/Quadruple.hpp"

using namespace std;


class OperationHelper{
private:

    int globalMemoryOffset;

    MemoryFrame* globalFrame;
    MemoryFrame* currentFrame;

    void callForDivisionbyCeroError(){
        cout<<"ERROR: Division by 0"<<endl;
        exit(0);
    }

    Type getTypeFromContext(int value){

        Type type;

        if(value<globalMemoryOffset){
                type = globalFrame->getType(value);

        }else{
                type = currentFrame->getType(value);

        }

        return type;
    }


    //Retrieve values

    int retrieveIntegerValueFromContext(int value){

        if(getScope(value) == GLOBAL_){
            return globalFrame->getIntegerValue(value);
        }else{
            return currentFrame->getIntegerValue(value);
        }

    }

    float retrieveFloatValueFromContext(int value){

        if(getScope(value) == GLOBAL_){
            return globalFrame->getFloatValue(value);
        }else{
            return currentFrame->getFloatValue(value);
        }

    }

    string retrieveStringValueFromContext(int value){

        if(getScope(value) == GLOBAL_){
            return globalFrame->getStringValue(value);
        }else{
            return currentFrame->getStringValue(value);
        }

    }

    bool retrieveBooleanValueFromContext(int value){

        if(getScope(value) == GLOBAL_){
            return globalFrame->getBooleanValue(value);
        }else{
            return currentFrame->getBooleanValue(value);
        }

    }


    //Set Values

    void setValueFromContext(int memDir, int store){
        
        if(getScope(memDir) == GLOBAL_){
            return globalFrame->setValue(memDir,store);
        }else{
            return currentFrame->setValue(memDir,store);
        }
    }

    void setValueFromContext(int memDir, float store){
        
        if(getScope(memDir) == GLOBAL_){
            return globalFrame->setValue(memDir,store);
        }else{
            return currentFrame->setValue(memDir,store);
        }
    }

    void setValueFromContext(int memDir, string store){
        
        if(getScope(memDir) == GLOBAL_){
            return globalFrame->setValue(memDir,store);
        }else{
            return currentFrame->setValue(memDir,store);
        }
    }

    void setValueFromContext(int memDir, bool store ){
        
        if(getScope(memDir) == GLOBAL_){
            return globalFrame->setValue(memDir,store);
        }else{
            return currentFrame->setValue(memDir,store);
        }
    }
    

    DeclarationState getScope(int value){
        DeclarationState scope;

        if(value<globalMemoryOffset){
                return GLOBAL_;

        }else{
            return LOCAL_;

        }

    }
  
    
public:

    OperationHelper(int offset, MemoryFrame* globalFrame_, MemoryFrame* currentFrame_){
        globalMemoryOffset = offset;
        currentFrame = currentFrame_;
        globalFrame = globalFrame_;
    }

    void additionOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(leftType==INTEGER_ && rightType == INTEGER_){
            int result = retrieveIntegerValueFromContext(leftOperand) + retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            float result = retrieveIntegerValueFromContext(leftOperand) + retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            float result = retrieveFloatValueFromContext(leftOperand) + retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            float result = retrieveFloatValueFromContext(leftOperand) + retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==STRING_ && rightType == STRING_){
            string result = retrieveStringValueFromContext(leftOperand) + retrieveStringValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    void substractionOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(leftType==INTEGER_ && rightType == INTEGER_){
            int result = retrieveIntegerValueFromContext(leftOperand) - retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            float result = retrieveIntegerValueFromContext(leftOperand) - retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            float result = retrieveFloatValueFromContext(leftOperand) - retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            float result = retrieveFloatValueFromContext(leftOperand) - retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    void multiplicationOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(leftType==INTEGER_ && rightType == INTEGER_){
            float result = retrieveIntegerValueFromContext(leftOperand) * retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            float result = retrieveIntegerValueFromContext(leftOperand) * retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            float result = retrieveFloatValueFromContext(leftOperand) * retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            float result = retrieveFloatValueFromContext(leftOperand) * retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    void divisionOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(leftType==INTEGER_ && rightType == INTEGER_){

            if (retrieveIntegerValueFromContext(rightOperand) == 0)
            callForDivisionbyCeroError();

            float result = retrieveIntegerValueFromContext(leftOperand) / retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            if (retrieveIntegerValueFromContext(rightOperand) == 0.0f)
            callForDivisionbyCeroError();

            float result = retrieveIntegerValueFromContext(leftOperand) / retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            if (retrieveIntegerValueFromContext(rightOperand) == 0)
            callForDivisionbyCeroError();
            float result = retrieveFloatValueFromContext(leftOperand) / retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            if (retrieveIntegerValueFromContext(rightOperand) == 0.0f)
            callForDivisionbyCeroError();
            float result = retrieveFloatValueFromContext(leftOperand) / retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    

    
};



