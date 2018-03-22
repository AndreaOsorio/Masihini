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

enum Operand
{
    ADD_,
    SUBS_,
    MULT_
};

enum DeclarationState
{
    GLOBAL_,
    LOCAL_

};