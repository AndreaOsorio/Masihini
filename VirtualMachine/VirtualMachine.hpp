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
                case GOTO_: goto_(quad); break; 
                case ENDPROG_: exitExec(); break;
            }


        }

    }


};



