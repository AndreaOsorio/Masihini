
#ifndef Type_hpp
#define Type_hpp
#include <iostream>
/**

*/
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
    ADD_,//Ready
    SUBS_,//Ready
    MULT_,//Ready
    DIV_,//Ready
    GT_,//Ready
    LT_,//Ready
    LE_,//Ready
    GE_,//Ready
    EE_,//Ready
    NOT_,//Ready
    AND_,//Ready
    OR_,//Ready
    EQ_,//Ready
    FAKE_BTTM_,//Doesn't apply
    SPEAK_,//Ready
    ACCEL_,//Ready
    JUMP_,//Ready
    STOP_,//Ready
    ROT_,//Ready
    /** Non Expression-Related Operators */
    GOTOF_,//Ready
    GOTO_,//Ready
    ENDPROC_,
    RETURN_,
    ERA_,
    PARAMETER_,
    GOSUB_,
    /** Array related Operators */
    VERIFY_,
    ENDPROG_//Ready
};

enum DeclarationState
{
    GLOBAL_,
    LOCAL_

};

#endif