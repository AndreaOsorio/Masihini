#pragma once
#include <iostream>
#include <string>
#include "./DeclarationHelper.hpp"
#include "./SemanticValidationHelper.hpp"
#include "./Dimension.hpp"

using namespace std;

/**
 * This class contains the  DIMENSIONAL declaration helper.
 * It manages the information of the dimensions from the current declared function or variable.
 * It is a helper of the Declarartion helper.
 */

class DimensionalDeclarationHelper{

private:

    DeclarationHelper* declarationHelper;
    SemanticValidationHelper* semanticHelper;
    CompilationErrorHandler* errorHandler;

    bool isConstant = false;
    bool isDeclaring = false;
    
public:

    DimensionalDeclarationHelper(DeclarationHelper* dHelper, SemanticValidationHelper* sHelper){
        declarationHelper = dHelper;
        semanticHelper = sHelper;
    }

    void verifyDeclaration(){
        if(!isConstant){
            errorHandler->callForError(TYPE_MISMATCH, "");
        }
    }

    void setIsConstant(bool newState){
        isConstant = newState;
    }

    bool getIsConstant(){
        return isConstant;
    }

    void setIsDeclaring(bool newState){
        isDeclaring = newState;
    }

    bool getIsDeclaring(){
        return isDeclaring;
    }







};
