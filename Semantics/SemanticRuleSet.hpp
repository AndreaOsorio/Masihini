#pragma once
#include <stdio.h>
#include <unordered_set>
#include <iostream>
#include <string>
#include "./Type.hpp"





using namespace std;

class SemanticRuleSet{
private:

    //This means multiplication and division
    Type isTier0Allowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return INTEGER_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return FLOAT_;

        return t;
    }

    

    //This means addition
    Type isTier1Allowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return INTEGER_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return FLOAT_;
        
        if(rightOperand == STRING_ && leftOperand == STRING_) return STRING_;


        return t;
    }


    //This means substraction
     Type isTier2Allowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return INTEGER_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return FLOAT_;


        return t;
    }

    //This means relop
    Type isTier3Allowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return BOOLEAN_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return BOOLEAN_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return BOOLEAN_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return BOOLEAN_;


        return t;
    }


    //This means AND OR operations
    Type isTier4Allowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == BOOLEAN_ && leftOperand == BOOLEAN_) return BOOLEAN_;


        return t;
    }

    //means NOT! operator
    Type isTier5Allowed(Type rightOperand){

        Type t = VOID_;

        if(rightOperand == BOOLEAN_ ) return BOOLEAN_;


        return t;
    }

    //means the EQ operator
    Type isTier6Allowed(Type rightOperand, Type leftOperand){

        Type t = VOID_;

        if(rightOperand == leftOperand) return rightOperand;


        return t;
    }



    //This means equals equals operator
    Type isTier7Allowed(Type rightOperand, Type leftOperand){

        if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return BOOLEAN_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return BOOLEAN_;
        if(rightOperand == STRING_ && leftOperand == STRING_) return BOOLEAN_;
        if(rightOperand == BOOLEAN_ && leftOperand == BOOLEAN_) return BOOLEAN_;


    }    

    //This means division
    Type isTier8Allowed(Type rightOperand, Type leftOperand){
         if(rightOperand == INTEGER_ && leftOperand == INTEGER_) return FLOAT_;
        if(rightOperand == INTEGER_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == FLOAT_) return FLOAT_;
        if(rightOperand == FLOAT_ && leftOperand == INTEGER_) return FLOAT_;

    }

    //This means accel / rot
    Type isTier9Allowed(Type rightOperand){

        Type t = VOID_;

        if(rightOperand == INTEGER_ ) return INTEGER_;
        if(rightOperand == FLOAT_ ) return FLOAT_;

        return t;
    }
    
    
    
public:

    Type isAllowed(Type rightOperand, Type leftOperand, Operator op){

        Type p = VOID_;

        switch (op){
            case MULT_: p = isTier0Allowed(rightOperand, leftOperand); break;
            case DIV_: p = isTier8Allowed(rightOperand, leftOperand);  break;
            case ADD_: p = isTier1Allowed(rightOperand, leftOperand);  break;
            case SUBS_: p = isTier2Allowed(rightOperand, leftOperand); break;
            case GT_ : p = isTier3Allowed(rightOperand, leftOperand);  break;
            case LT_ : p = isTier3Allowed(rightOperand, leftOperand);  break;
            case LE_ : p = isTier3Allowed(rightOperand, leftOperand);  break;
            case GE_ : p = isTier3Allowed(rightOperand, leftOperand);  break;
            case AND_: p = isTier4Allowed(rightOperand, leftOperand);  break;
            case OR_ : p = isTier4Allowed(rightOperand, leftOperand);  break;
            case NOT_: p = isTier5Allowed(rightOperand);  break;
            case EQ_ : p = isTier6Allowed(rightOperand, leftOperand);  break;
            case EE_ : p = isTier7Allowed(rightOperand, leftOperand);  break;
            case ACCEL_: p = isTier9Allowed(rightOperand);  break;
            case ROT_: p = isTier9Allowed(rightOperand);  break;
        }




        return p;
    }

    
};