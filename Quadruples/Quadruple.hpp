

#pragma once
#include <stdio.h>
#include <iostream>
#include "../Semantics/Type.hpp"

using namespace std;


class Quadruple{
private:
   
    Operator operator_;
    int leftOperand;
    int rightOperand;
    int result;
    
    
public:

    Quadruple(Operator oper, int leftOper, int rightOper, int res){

        operator_ = oper;
        leftOperand = leftOper;
        rightOperand = rightOper;
        result = res;

    }

    Operator getOperator(){
        return operator_;
    }

    void setResult(int res){
        result = res;
    }

    void print(){

        switch (operator_){

            case ADD_: cout<< "+ "; break;
            case SUBS_: cout<<"- "; break;
            case MULT_: cout<<"* "; break;
            case DIV_: cout<<"/ "; break;
            case GT_: cout<<"> "; break;
            case LT_: cout<<"< "; break;
            case LE_: cout<< "<= "; break;
            case GE_: cout<< ">= "; break;
            case EE_: cout<< "== "; break;
            case NOT_:cout<<"! "; break;
            case AND_: cout<<"& "; break;
            case OR_: cout<< "| "; break;
            case EQ_: cout<< "= "; break;
            case GOTOF_: cout << "GOTOF "; break;
            case GOTO_: cout << "GOTO "; break;
            case ENDPROC_: cout << "ENDPROC "; break;
            case RETURN_: cout << "RETURN "; break;
            case ERA_: cout << "ERA_ "; break;
            case PARAMETER_: cout << "PARAMETER_ "; break;
            case GOSUB_: cout << "GOSUB_ "; break;
        }

        cout <<leftOperand<<" , "<<rightOperand<<" , "<<result<<endl;
        
    }
    

    
};



