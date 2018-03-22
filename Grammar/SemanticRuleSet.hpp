#pragma once
#include <stdio.h>
#include <unordered_set>
#include <iostream>
#include <string>
#include "Type.hpp"





using namespace std;

class SemanticRuleSet{
private:

    //This means multiplication and division
    Type isTier0Alowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return FLOAT_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return FLOAT_;

        return t;
    }

    //This means addition
    Type isTier1Alowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return INTEGER_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return FLOAT_;
        
        if(rightOperand == STRING_ && leftOperand == STRING_) return STRING_;


        return t;
    }


    //This means substraction
     Type isTier2Alowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return INTEGER_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return FLOAT_;


        return t;
    }

    //This means relop
    Type isTier3Alowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return BOOLEAN_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return BOOLEAN_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return BOOLEAN_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return BOOLEAN_;


        return t;
    }

    //This means AND OR operations
    Type isTier4Alowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == BOOLEAN_ && leftOperand == BOOLEAN_) return BOOLEAN_;


        return t;
    }


    
    
    
    
public:

    Type isAllowed(Type rightOperand, Type leftOperand, Operator op){

        Type p = VOID_;

        switch (op){
            case MULT_: p = isTier0Alowed(rightOperand, leftOperand); break;
            case DIV_: p = isTier0Alowed(rightOperand, leftOperand);  break;
            case ADD_: p = isTier1Alowed(rightOperand, leftOperand);  break;
            case SUBS_: p = isTier2Alowed(rightOperand, leftOperand); break;
            case GT_ : p = isTier3Alowed(rightOperand, leftOperand);  break;
            case LT_ : p = isTier3Alowed(rightOperand, leftOperand);  break;
            case LE_ : p = isTier3Alowed(rightOperand, leftOperand);  break;
            case GE_ : p = isTier3Alowed(rightOperand, leftOperand);  break;
            case EE_ : p = isTier3Alowed(rightOperand, leftOperand);  break;
            case AND_: p = isTier4Alowed(rightOperand, leftOperand);  break;
            case OR_ : p = isTier4Alowed(rightOperand, leftOperand);  break;
        }




        return p;
    }

    
};