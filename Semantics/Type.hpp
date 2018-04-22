
#ifndef Type_hpp
#define Type_hpp
#include <iostream>
/**

*/
enum Type
{
    STRING_,  //0
    BOOLEAN_, //1
    INTEGER_, //2
    FLOAT_,   //3
    VOID_     //4
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
    VER_,
    ENDPROG_//Ready
};

enum DeclarationState
{
    GLOBAL_,
    LOCAL_

};

#endif