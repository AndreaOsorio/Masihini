//
//  FuncDir.hpp
//  CompilerTestProject
//
//  Created by Ruben Hidalgo on 3/9/18.
//  Copyright © 2018 Ruben Hidalgo. All rights reserved.
//

#pragma once
#include <stdio.h>
#include <unordered_set>
#include <iostream>
#include <string>
#include "VarTable.hpp"
#include "FuncNode.hpp"




using namespace std;

class FuncDir{
private:
    unordered_set<FuncNode, FuncNodeHasher, FuncNodeComparator> funcTable;
    
    
    
public:
    void insertNode(FuncNode* node){
        
        auto res = funcTable.insert(*node);
        
        
        
        if (res.second == false)

            

            std::cout << "ERROR: Function \""<< node->getId() <<"\" has been declared previously" << std::endl;

        
        
    }

    
};



