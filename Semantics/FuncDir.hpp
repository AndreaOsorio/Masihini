//
//  FuncDir.hpp
//  CompilerTestProject
//
//  Created by Ruben Hidalgo on 3/9/18.
//  Copyright © 2018 Ruben Hidalgo. All rights reserved.
//

#ifndef FuncDir_hpp
#define FuncDir_hpp
#include <stdio.h>
#include <unordered_set>
#include <iostream>
#include <string>
#include <vector>
#include "./VarTable.hpp"
#include "./FuncNode.hpp"




using namespace std;

class FuncDir{
private:
    unordered_set<FuncNode, FuncNodeHasher, FuncNodeComparator> funcTable;
    vector <FuncNode*> funcList;
    
    
    
public:
    string insertNode(FuncNode* node){
        
        auto res = funcTable.insert(*node);
        funcList.push_back(node);
        string message = "";
        
        
        if (res.second == false)
            message = "Function \"" + node->getId() + "\" has been defined previously";
        

        return message;
    }

    FuncNode* getFunc(int index){
        return funcList.at(index);
    }

    vector <FuncNode*>* getFuncList(){
        return &funcList;
    }

    int search(string name){
        
        int count =0;
        for ( auto &i : funcList ) {    

            string id = i->getId();

            if(name.compare(id)==0){
                return count;
            }

            count++;

        }
      return -1;

    }

    
};

#endif

