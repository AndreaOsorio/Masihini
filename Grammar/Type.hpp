#pragma once

#include <iostream>


enum Type
{
    STRING_,
    BOOLEAN_,
    INTEGER_,
    FLOAT_,
    VOID_
};

enum Operator
{
    ADD_,
    SUBS_,
    MULT_,
    DIV_
};

enum DeclarationState
{
    GLOBAL_,
    LOCAL_

};