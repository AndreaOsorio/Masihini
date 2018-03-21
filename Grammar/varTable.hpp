//
//  VarTable.hpp
//  CompilerTestProject
//
//  Created by Ruben Hidalgo on 3/8/18.
//  Copyright © 2018 Ruben Hidalgo. All rights reserved.
//


#pragma once
#include <stdio.h>
#include <unordered_set>
#include <iostream>
#include <string>
#include "VarNode.hpp"


using namespace std;

class VarTable{
    private:

    unordered_set<VarNode, VarNodeHasher, VarNodeComparator> varTable;
    
    
    public:
    VarTable( ){
        
    }
    
    string insertNode(VarNode* node){
        
        auto res = varTable.insert(*node);

        string message = "";
        
        if (res.second == false)
            message = "Variable \"" + node->getId() + "\" has been defined previously";

        return message;
        
    }

    
    bool isContained(VarTable *globalTable, VarNode element)
    {
        const bool result = globalTable->varTable.find(element) != globalTable->varTable.end();
        return result;
    }
    


    ~VarTable(){
        
    }

};


