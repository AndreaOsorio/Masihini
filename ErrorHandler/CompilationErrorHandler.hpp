

#pragma once
#include <iostream>
#include <string>
#include "./ErrorType.hpp"

using namespace std;



class CompilationErrorHandler{

private:


    void callForLocalRedefinitionError(string message){
        cout<<"Variable \"" + message + "\" was previously declared on the current context"<<endl;
        exit(0);
    }

    void callForGlobalRedefinitionError(string message){
        cout<<"Variable \"" + message + "\" was previously declared as a global variable"<<endl;
        exit(0);
        
    }

    void callForFunctionRedefinitionError(string message){
        cout<<"Function \"" + message + "\" was previously declared"<<endl;
        exit(0);   
    }

    void callForTypeMismatchError(string message){
        cout<<"Type mismatch, operation cannot be performed"<<endl;
        exit(0); 
    }

    void callForNonDeclaredVariableError(string message){
        cout<<"Variable \"" + message + "\" has not been declared"<<endl;
        exit(0); 
    }

    void callForNonDeclaredFunctionError(string message){
        cout<<"Function \"" + message + "\" has not been declared"<<endl;
        exit(0); 
    }

    void callForFewParametersError(string message){
        cout<<"Function call \"" + message + "\" has fewer parameters than needed"<<endl;
        exit(0); 
    }

    void callForTooManyParametersError(string message){
        cout<<"Function call \"" + message + "\" is expecting less parameters"<<endl;
        exit(0); 
    }

    void callForReturnStatementMissingError(string message){
        cout<<"Function \"" + message + "\" must have return statement at the end"<<endl;
        exit(0); 
    }

    void callForArrayMismatchError(string message){
        cout<<"Array dimension mismatch, operation cannot be performed"<<endl;
        exit(0); 
    }

    void callForArrayParameterMismatchError(string message){
        cout<<"Function call \"" + message + "\" has parameters of different dimensions"<<endl;
        exit(0);
    }

    
    
public:


    void callForError(ErrorType type, string message){

        switch(type){
            case LOCAL_REDEFINITION: callForLocalRedefinitionError(message);break;
            case GLOBAL_REDEFINITION: callForGlobalRedefinitionError(message);break;
            case FUNCTION_REDEFINITION: callForFunctionRedefinitionError(message);break;
            case TYPE_MISMATCH: callForTypeMismatchError(message);break;
            case NON_DECLARED_VARIABLE: callForNonDeclaredVariableError(message);break;
            case TOO_FEW_PARAMETERS: callForFewParametersError(message);break;
            case TOO_MANY_PARAMETERS: callForTooManyParametersError(message);break;
            case NON_DECLARED_FUNCTION: callForNonDeclaredFunctionError(message); break;
            case RETURN_STATEMENT_MISSING: callForReturnStatementMissingError(message); break;
            case ARRAY_MISMATCH: callForArrayMismatchError(message); break;
            case ARRAY_PARAMETERS_MISMATCH: callForArrayParameterMismatchError(message); break;

        }

    }


    
};



