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
    stack <MemoryFrame*> memoryStack;
    MemoryFrame* globalMemoryFrame;
    MemoryFrame* currentFrame;
    int globalMemoryOffset = 25000;

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
        execPointer = helper.gotoFOperation(quad);

    }

    void exitExec(){

        cout<<"Execution Sucessful!"<<endl;
        exit (0);

    }


    void printQuads(){

      int count = 0;
      for ( auto &i : *quadrupleSet ) {

            cout <<count<< ".- ";
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


    
    
    
public:
    
    VirtualMachine(vector <Quadruple*>* quadSet, vector<FuncNode*>* funcDir, MemoryFrame* globalMemFrame ){
       
            quadrupleSet = quadSet;
            functionDirectory = funcDir;
            globalMemoryFrame = globalMemFrame;

            cout<<"------------------------ Exec output---------------------"<<endl;
            printQuads();
            init();
            run();

    }


    void run(){

        for ( auto &i : *quadrupleSet ) {

            Quadruple* quad = quadrupleSet->at(execPointer);
            Operator operator_ = quad->getOperator();

            //Any action that alters exec pointer does not add to the counter
            switch (operator_){
                case ADD_: addition(quad); execPointer++; break;
                case SUBS_: substraction(quad); execPointer++; break;
                case MULT_: multiplication(quad); execPointer++; break;
                case DIV_: division(quad); execPointer++; break;
                case GT_: greaterThan(quad); execPointer++; break;
                case LT_: greaterThan(quad); execPointer++; break;
                case LE_: lessOrEquals(quad); execPointer++; break;
                case GE_: greaterOrEquals(quad); execPointer++; break;
                case EE_: equalsEquals(quad); execPointer++; break;
                case NOT_: notOp(quad); execPointer++; break;
                case AND_: andOp(quad); execPointer++; break;
                case OR_: orOp(quad); execPointer++; break;
                case GOTOF_: gotoF_(quad); break; 
                case GOTO_: goto_(quad); break; 
                case ENDPROG_: exitExec(); break;
            }


        }

    }


};



