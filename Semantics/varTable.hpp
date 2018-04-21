//
//  VarTable.hpp
//  CompilerTestProject
//
//  Created by Ruben Hidalgo on 3/8/18.
//  Copyright © 2018 Ruben Hidalgo. All rights reserved.
//


#ifndef VarTable_hpp
#define VarTable_hpp

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
        VarNode elem (id, VOID_, -1);
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
        VarNode elem (id, type, -1);
        string message = "";
        const bool result = varTable.find(elem) != varTable.end();

        if(result){
            message = "Refedinition of global variable \"" + id + "\" ";
        }
        return message;
    }

    int search(string id){

        if(isContainedInTable(id)){
            VarNode elem (id, VOID_, -1);
            auto it = this->varTable.find(elem);
            return it->getMemDir();

        }

        return -1;

    }
    


    ~VarTable(){
        
    }

};

#endif
