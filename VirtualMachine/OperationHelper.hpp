#ifndef OperationHelper_hpp
#define OperationHelper_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include "../Semantics/Type.hpp"
#include "../Semantics/FuncDir.hpp"
#include "../Memory/MemoryFrame.hpp"
#include "../Quadruples/Quadruple.hpp"

using namespace std;


class OperationHelper{
private:

    int globalMemoryOffset;
    

    MemoryFrame* globalFrame;
    MemoryFrame* currentFrame;

    void callForDivisionbyCeroError(){
        cout<<"RUNTIME ERROR: Division by 0"<<endl;
        exit(0);
    }

    void callForIndexOutOfBounds(){
        cout<<"RUNTIME ERROR: Index out of bounds"<<endl;
        exit(0);
    }

    void callForSystemMismatchError(string oper)
    {
        cout<<oper<<" does not support this operation"<<endl;
        exit(0);
    }

    

    Type getTypeFromContext(int value){

        Type type;


      if (value > 0){

            if(value<globalMemoryOffset){
                  type = globalFrame->getType(value);

            }else{
                
                  type = currentFrame->getType(value);

            }

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
            int result = retrieveIntegerValueFromContext(leftOperand) * retrieveIntegerValueFromContext(rightOperand);
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

            if (retrieveFloatValueFromContext(rightOperand) == 0.0f)
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
            if (retrieveFloatValueFromContext(rightOperand) == 0.0f)
            callForDivisionbyCeroError();
            float result = retrieveFloatValueFromContext(leftOperand) / retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    void assignmentOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);


        if(leftType==INTEGER_){
            setValueFromContext(memDir , retrieveIntegerValueFromContext(leftOperand));
        }

        if(leftType==FLOAT_){
            setValueFromContext(memDir , retrieveFloatValueFromContext(leftOperand));
        }

        if(leftType==BOOLEAN_){
            setValueFromContext(memDir , retrieveBooleanValueFromContext(leftOperand));
        }

        if(leftType==STRING_){
            setValueFromContext(memDir , retrieveStringValueFromContext(leftOperand));
        }

    }


    void greaterThanOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(leftType==INTEGER_ && rightType == INTEGER_){
            bool result = retrieveIntegerValueFromContext(leftOperand) > retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            bool result = retrieveIntegerValueFromContext(leftOperand) > retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            bool result = retrieveFloatValueFromContext(leftOperand) > retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            bool result = retrieveFloatValueFromContext(leftOperand) > retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

      void lessThanOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);

        if(leftType==INTEGER_ && rightType == INTEGER_){
            bool result = retrieveIntegerValueFromContext(leftOperand) < retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            bool result = retrieveIntegerValueFromContext(leftOperand) < retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            bool result = retrieveFloatValueFromContext(leftOperand) < retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            bool result = retrieveFloatValueFromContext(leftOperand) < retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

     void lessOrEqualsOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(leftType==INTEGER_ && rightType == INTEGER_){
            bool result = retrieveIntegerValueFromContext(leftOperand) <= retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            bool result = retrieveIntegerValueFromContext(leftOperand) <= retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            bool result = retrieveFloatValueFromContext(leftOperand) <= retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            bool result = retrieveFloatValueFromContext(leftOperand) <= retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    void greaterOrEqualsOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(leftType==INTEGER_ && rightType == INTEGER_){
            bool result = retrieveIntegerValueFromContext(leftOperand) >= retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            bool result = retrieveIntegerValueFromContext(leftOperand) >= retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            bool result = retrieveFloatValueFromContext(leftOperand) >= retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            bool result = retrieveFloatValueFromContext(leftOperand) >= retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    void equalsEqualsOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(leftType==INTEGER_ && rightType == INTEGER_){
           
            bool result = retrieveIntegerValueFromContext(leftOperand) == retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==INTEGER_ && rightType == FLOAT_){
            bool result = retrieveIntegerValueFromContext(leftOperand) == retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == INTEGER_){
            bool result = retrieveFloatValueFromContext(leftOperand) == retrieveIntegerValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }

        if(leftType==FLOAT_ && rightType == FLOAT_){
            bool result = retrieveFloatValueFromContext(leftOperand) == retrieveFloatValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    void notOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);


        if(rightType==BOOLEAN_){
            bool result = !retrieveBooleanValueFromContext(rightOperand);
            setValueFromContext(memDir, result);
        }
    }

    void andOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);

        if(leftType==BOOLEAN_ && rightType == BOOLEAN_){
            bool result = retrieveBooleanValueFromContext(leftOperand) && retrieveBooleanValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    void orOperation(Quadruple* quad){

        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getRightOperand();
        int memDir = quad->getResult();

        Type leftType = getTypeFromContext(leftOperand);
        Type rightType = getTypeFromContext(rightOperand);

        if(leftType==BOOLEAN_ || rightType == BOOLEAN_){
            bool result = retrieveBooleanValueFromContext(leftOperand) || retrieveBooleanValueFromContext(rightOperand);
            setValueFromContext(memDir,result );
        }
    }

    int gotoFOperation(Quadruple* quad){

     


        int leftOperand = quad->getLeftOperand();
        int result= quad->getResult();
        Type leftType = getTypeFromContext(leftOperand);

        if(leftType==BOOLEAN_){
            bool value = retrieveBooleanValueFromContext(leftOperand);
            if( value == false){

                return result;
            }
        }

        return -1;
    }

    void speakOperation(Quadruple* quad){

        int result= quad->getResult();

        int dimension = quad->getLeftOperand();
        if(dimension == 1)
        {
            result = retrieveIntegerValueFromContext(result);
        }

        Type type = getTypeFromContext(result);


        if(type == STRING_)
        cout<<"SPEAK "<<retrieveStringValueFromContext(result)<<endl;

        if(type == FLOAT_)
        cout<<"SPEAK "<<retrieveFloatValueFromContext(result)<<endl;

        if(type == INTEGER_)
        cout<<"SPEAK "<<retrieveIntegerValueFromContext(result)<<endl;

        if(type == BOOLEAN_)
        cout<<"SPEAK "<<retrieveBooleanValueFromContext(result)<<endl;

    }


    void accelOperation(Quadruple* quad){

        int result= quad->getResult();

        int dimension = quad->getLeftOperand();
        if(dimension = 1)
        {
            result = retrieveIntegerValueFromContext(result);
        }

        Type type = getTypeFromContext(result);

        if(type == FLOAT_)
        cout<<"ACCEL "<<retrieveFloatValueFromContext(result)<<endl;

        if(type == INTEGER_)
        cout<<"ACCEL "<<retrieveIntegerValueFromContext(result)<<endl;

        if(type == BOOLEAN_ || type == STRING_)
        callForSystemMismatchError("Move");

    }

    void rotOperation(Quadruple* quad){

        int result= quad->getResult();

        int dimension = quad->getLeftOperand();
        if(dimension = 1)
        {
            result = retrieveIntegerValueFromContext(result);
        }

        Type type = getTypeFromContext(result);

        if(type == FLOAT_)
        cout<<"ROT "<<retrieveFloatValueFromContext(result)<<endl;

        if(type == INTEGER_)
        cout<<"ROT "<<retrieveIntegerValueFromContext(result)<<endl;
        
        if(type == BOOLEAN_ || type == STRING_)
        callForSystemMismatchError("Rot");

    }

    void jumpOperation(){
        cout<<"JUMP "<<endl;
    }

    void stopOperation(){
        cout<<"STOP "<<endl;
    }


    void assignParameter(FuncNode* functionCalled, MemoryFrame* frameCalled, Quadruple* quad){

        int valueDir = quad->getRightOperand();
        Type typeValue = getTypeFromContext(valueDir);

        int index = quad->getResult();
        int paramDir = functionCalled->getParameterDirAt(index);
        

        if(typeValue == INTEGER_){
            int value = retrieveIntegerValueFromContext(valueDir);
            currentFrame = frameCalled;
            setValueFromContext(paramDir, value);
        }

        if(typeValue == FLOAT_){
            float value = retrieveFloatValueFromContext(valueDir);
            currentFrame = frameCalled;
            setValueFromContext(paramDir, value);
        }

         if(typeValue == STRING_){
            string value = retrieveStringValueFromContext(valueDir);
            currentFrame = frameCalled;
            setValueFromContext(paramDir, value);
        }

         if(typeValue == BOOLEAN_){
            bool value = retrieveBooleanValueFromContext(valueDir);
            currentFrame = frameCalled;
            setValueFromContext(paramDir, value);
        }

    }

    int returnOperation(Quadruple* quad){

        int result = quad->getResult();
        Type type = getTypeFromContext(result);
        int memOffset = quad->getLeftOperand();

        int memDir = 0;

        for(int i = 0; i<memOffset; i++){

            int res = 0;

            if(type == INTEGER_){
                int value = retrieveIntegerValueFromContext(result);
                res = globalFrame->registerValue(value);
            }

            if(type == FLOAT_){
                float value = retrieveFloatValueFromContext(result);
                res = globalFrame->registerValue(value);
            }

            if(type == STRING_){
                string value = retrieveStringValueFromContext(result);
                res = globalFrame->registerValue(value);
            }

            if(type == BOOLEAN_){
                bool value = retrieveBooleanValueFromContext(result);
                res = globalFrame->registerValue(value);
            }

            if(i == 0){ memDir = res; }

        }

        return memDir;

    }



    
    void verifyOperation(Quadruple* quad){
        int leftOperand = quad->getLeftOperand();
        int index = retrieveIntegerValueFromContext(leftOperand);
        int size = quad->getResult();
        //cout<<" Verify "<< index << " in "<< size<<endl;
        if(index >= size || index < 0){
            callForIndexOutOfBounds();
        }
    }

    void dirOperation(Quadruple* quad){
        
        int leftOperand = quad->getLeftOperand();
        int rightOperand = quad->getResult();
        int memDir = retrieveIntegerValueFromContext(rightOperand);

        Type leftType = getTypeFromContext(leftOperand);

        if(leftType==INTEGER_){
            setValueFromContext(memDir, retrieveIntegerValueFromContext(leftOperand));
        }

        if(leftType==FLOAT_){
            setValueFromContext(memDir , retrieveFloatValueFromContext(leftOperand));
        }

        if(leftType==BOOLEAN_){
            setValueFromContext(memDir , retrieveBooleanValueFromContext(leftOperand));
        }

        if(leftType==STRING_){
            setValueFromContext(memDir , retrieveStringValueFromContext(leftOperand));
        }
    }

    void arrOperation(Quadruple* quad){
        
        int leftOperand = quad->getLeftOperand();
        int memDir = quad->getResult();

        int value = retrieveIntegerValueFromContext(leftOperand);
        Type type = getTypeFromContext(leftOperand);

        if(type==INTEGER_){
            int res = retrieveIntegerValueFromContext(value);
            setValueFromContext(memDir, res);
        }

        if(type==FLOAT_){
            float res = retrieveFloatValueFromContext(value);
            setValueFromContext(memDir, res);
        }

        if(type==BOOLEAN_){
            bool res = retrieveBooleanValueFromContext(value);
            setValueFromContext(memDir , res);
        }

        if(type==STRING_){
            string res = retrieveStringValueFromContext(value);
            setValueFromContext(memDir , res);
        }

    }


    
};

#endif

