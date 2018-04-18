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

    bool isContainedInTable(string id)
    {
        VarNode elem (id, VOID_);
        const bool result = varTable.find(elem) != varTable.end();
        return result;
    }
    
    
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

    
    string isContained(string id, Type type)
    {
        VarNode elem (id, type);
        string message = "";
        const bool result = varTable.find(elem) != varTable.end();

        if(result){
            message = "Refedinition of global variable \"" + id + "\" ";
        }
        return message;
    }

    int search(string id){

        if(isContainedInTable(id)){
            VarNode elem (id, VOID_);
            auto it = this->varTable.find(elem);
            return it->getMemDir();

        }

        return -1;

    }
    


    ~VarTable(){
        
    }

};


