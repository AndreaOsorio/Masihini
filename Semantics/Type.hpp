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
    DIV_,
    GT_,
    LT_,
    LE_,
    GE_,
    EE_,
    NOT_,
    AND_,
    OR_,
    EQ_,
    FAKE_BTTM_,
    SPEAK_,
    ACCEL_,
    JUMP_,
    STOP_,
    ROT_,
    //Non Expression-Related Operators
    POPRES_,
    GOTOF_,
    GOTO_,
    ENDPROC_,
    RETURN_,
    ERA_,
    PARAMETER_,
    GOSUB_,
    ENDPROG_
};

enum DeclarationState
{
    GLOBAL_,
    LOCAL_

