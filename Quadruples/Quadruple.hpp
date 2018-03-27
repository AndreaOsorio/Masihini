

#pragma once
#include <stdio.h>
#include "../Semantics/Type.hpp"



class Quadruple{
private:
   
    Operator operator_;
    int leftOperand;
    int rightOperand;
    int result;
    
    
public:

    Quadruple(Operator oper, int rightOper, int leftOper, int res){

        operator_ = oper;
        leftOperand = leftOper;
        rightOperand = rightOper;
        result = res;

    }
    

    
};



