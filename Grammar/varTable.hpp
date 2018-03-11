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
    
    void insertNode(VarNode* node){
        
        auto res = varTable.insert(*node);


        
        if (res.second == false)
            std::cout << "Failed to insert a thingy in VarTable" << std::endl;
        
    }

    
    bool isContained(VarTable *globalTable, VarNode element)
    {
        const bool result = globalTable->varTable.find(element) != globalTable->varTable.end();
        return result;
    }
    


    ~VarTable(){
        
    }

};


