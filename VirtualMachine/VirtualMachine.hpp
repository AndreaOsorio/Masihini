//
//  FuncDir.hpp
//  CompilerTestProject
//
//  Created by Ruben Hidalgo on 3/9/18.
//  Copyright © 2018 Ruben Hidalgo. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <vector>
#include <stack>
#include "../Quadruples/Quadruple.hpp"
#include "../Semantics/FuncDir.hpp"
#include "OperationHelper.hpp"


using namespace std;

class VirtualMachine{
private:

    //Execution Environment
    vector<Quadruple*>* quadrupleSet;
    vector<FuncNode*>* functionDirectory;
    int execPointer = 0;
    stack<int> execPointerPositionStack;
    stack <MemoryFrame*> memoryStack;
    MemoryFrame* globalMemoryFrame;
    MemoryFrame* currentFrame;
    MemoryFrame* calledFrame;
    FuncNode* calledFunction;

    int globalMemoryOffset;

    void init(){
        FuncNode* mainFuncNode = functionDirectory->at(functionDirectory->size()-1);
        memoryStack.push(mainFuncNode->getMemoryFrame());
        currentFrame = memoryStack.top();
    }




    void goto_(Quadruple* quad){

        int result = quad->getResult();
        execPointer = result;

    }

    void gotoF_(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        int res = helper.gotoFOperation(quad);

        if(res != -1){
            execPointer = res;
        }else{
            execPointer++;
        }

    }

    void exitExec(){

        cout<<"Execution Sucessful!"<<endl;
        exit (0);

    }


    void printQuads(){

      int count = 0;
      for ( auto &i : *quadrupleSet ) {

            cout <<count<< ".-\t";
            i->print();
            count++;
      }

    }

    void addition(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.additionOperation(quad);

    }

    void substraction(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.substractionOperation(quad);

    }

    void multiplication(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.multiplicationOperation(quad);

    }

    void division(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.divisionOperation(quad);

    }

    void greaterThan(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.greaterThanOperation(quad);

    }

    void lessThan(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.lessThanOperation(quad);

    }

    void lessOrEquals(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.lessOrEqualsOperation(quad);

    }

    void greaterOrEquals(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.greaterOrEqualsOperation(quad);

    }

    void equalsEquals(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.equalsEqualsOperation(quad);

    }

    void notOp(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.notOperation(quad);

    }

    void andOp(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.andOperation(quad);

    }

    void orOp(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.orOperation(quad);

    }

    void speak(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.speakOperation(quad);

    }

    void accel(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.accelOperation(quad);

    }

    void rot(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.rotOperation(quad);

    }

    void stopOp(){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.stopOperation();

    }

    void jump(){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.jumpOperation();

    }

     void assignment(Quadruple* quad){

        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.assignmentOperation(quad);

    }

    void eraOp(Quadruple* quad){
        int index = quad->getResult();
        calledFunction = functionDirectory->at(index);
        calledFrame = new MemoryFrame(calledFunction->getMemoryFrame());
    }

    void parameterOp(Quadruple* quad){
        OperationHelper helper(globalMemoryOffset, globalMemoryFrame, currentFrame);
        helper.assignParameter(calledFunction, calledFrame, quad);
    }

    void gosubOp(){
        memoryStack.push(calledFrame);
        currentFrame = memoryStack.top();
        execPointerPositionStack.push(execPointer);
        execPointer = calledFunction->getStartingInstruction();
        
    }



    
    
    
public:
    
    VirtualMachine(vector <Quadruple*>* quadSet, vector<FuncNode*>* funcDir, MemoryFrame* globalMemFrame, int offset ){
       
            quadrupleSet = quadSet;
            functionDirectory = funcDir;
            globalMemoryFrame = globalMemFrame;
            globalMemoryOffset = offset;

            cout<<"------------------------ Exec output---------------------"<<endl;
            printQuads();
            init();
            run();

    }


    void run(){

        while (true) {

            Quadruple* quad = quadrupleSet->at(execPointer);
            Operator operator_ = quad->getOperator();


            //Any action that alters exec pointer does not add to the counter
            switch (operator_){
                case ADD_: addition(quad); execPointer++; break;
                case SUBS_: substraction(quad); execPointer++; break;
                case MULT_: multiplication(quad); execPointer++; break;
                case DIV_: division(quad); execPointer++; break;
                case GT_: greaterThan(quad); execPointer++; break;
                case LT_: lessThan(quad); execPointer++; break;
                case LE_: lessOrEquals(quad); execPointer++; break;
                case GE_: greaterOrEquals(quad); execPointer++; break;
                case EE_: equalsEquals(quad); execPointer++; break;
                case NOT_: notOp(quad); execPointer++; break;
                case AND_: andOp(quad); execPointer++; break;
                case OR_: orOp(quad); execPointer++; break;
                case SPEAK_: speak(quad); execPointer++; break;
                case ACCEL_: accel(quad); execPointer++; break;
                case ROT_: rot(quad); execPointer++; break;
                case JUMP_: jump(); execPointer++; break;
                case STOP_: stopOp(); execPointer++; break;
                case EQ_: assignment(quad); execPointer++; break;
                case ERA_: eraOp(quad); execPointer++; break;
                case PARAMETER_: parameterOp(quad); execPointer++; break;
                case GOSUB_: gosubOp(); break;
                case GOTOF_: gotoF_(quad); break; 
                case GOTO_: goto_(quad); break; 
                case ENDPROC_: exitExec(); break;
            }


        }

    }


};



