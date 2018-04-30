#pragma once
#include <stdio.h>
#include <unordered_set>
#include <iostream>
#include <string>
#include "VarNode.hpp"
#include "Dimension.hpp"


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
    
    bool insertNode(VarNode* node){
        
        auto res = varTable.insert(*node);
        

        return res.second;
        
    }

    
    bool isContained(string id, Type type)
    {
        VarNode elem (id, type);
        const bool result = varTable.find(elem) != varTable.end();
        return result;
    }

    int search(string id){

        if(isContainedInTable(id)){
            VarNode elem (id, VOID_);
            auto it = this->varTable.find(elem);
            return it->getMemDir();

        }

        return -1;
    }

    Dimension* getDimensionInformation(string id){
        if(isContainedInTable(id)){
            VarNode elem (id, VOID_);
            auto it = this->varTable.find(elem);
            return it->getDimensions();
        }

        Dimension* noDimensions = new Dimension();
        return noDimensions;

    }


    ~VarTable(){
        
    }

};