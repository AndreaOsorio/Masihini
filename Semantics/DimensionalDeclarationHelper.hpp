#pragma once
#include <iostream>
#include <string>
#include "./DeclarationHelper.hpp"
#include "./SemanticValidationHelper.hpp"
#include "./Dimension.hpp"

using namespace std;

class DimensionalDeclarationHelper{

private:


    DeclarationHelper* declarationHelper;
    SemanticValidationHelper* semanticHelper;

    
    
public:

    DimensionalDeclarationHelper(DeclarationHelper* dHelper, SemanticValidationHelper* sHelper){
        declarationHelper = dHelper;
        semanticHelper = sHelper;
    }

};
