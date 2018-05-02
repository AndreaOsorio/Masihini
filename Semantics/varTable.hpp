#pragma once
#include <stdio.h>
#include <unordered_set>
#include <iostream>
#include <string>
#include "VarNode.hpp"
#include "Dimension.hpp"


/**
 * This class contains the symbol table
 * It manages the information from the current symbol table of a  function
 * It is a set of varNodes with a hasher and comparator that are handled by the id of the variable.
 */

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

    Dimension getDimensionInformation(string id){
        if(isContainedInTable(id)){
            VarNode elem (id, VOID_);
            auto it = this->varTable.find(elem);
            return it->getDimensions();
        }

        Dimension noDimensions;
        return noDimensions;

    }

    string getIdFromMemoryContext(int memDir){
        for (auto itr = varTable.begin(); itr != varTable.end(); ++itr) {
            /* ... process *itr ... */
            int thisMem = itr->getMemDir();
            if(thisMem == memDir){
                return itr->getId();
            }
        }
        return "NOT_FOUND";
    }


    ~VarTable(){
        
    }

};