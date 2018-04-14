//
//  FuncNode.hpp
//  CompilerTestProject
//
//  Created by Ruben Hidalgo on 3/9/18.
//  Copyright © 2018 Ruben Hidalgo. All rights reserved.
//

#ifndef FuncNode_hpp
#define FuncNode_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "./Type.hpp"
#include "./VarTable.hpp"
#include "../Memory/MemoryFrame.hpp"



#endif /* FuncNode_hpp */

using namespace std;

class FuncNode{
private:
    string id;
    Type type;
    VarTable *symbolTable;
    MemoryFrame *memoryFrame = new MemoryFrame();
    vector<int> parameters;
    
    
    
public:
    FuncNode( string identifier, Type dataType, VarTable* symbTable, MemoryFrame* memFrame){
        
        id = identifier;
        type = dataType;
        symbolTable = symbTable;
        memoryFrame = memFrame;
        
    }

    void addParameter(int param){
        parameters.push_back(param);
    }

    string getId() const{
        return id;
    }

    VarTable* getSymbolTable(){
        return symbolTable;
    }

    MemoryFrame* getMemoryFrame(){
        return memoryFrame;
    }
    
    
};


namespace std
{
    template<> struct hash<FuncNode>
    {
        size_t
        operator()(const FuncNode & obj) const
        {
            return hash<string>()(obj.getId());
        }
    };
    
}

struct FuncNodeHasher
{
    size_t
    operator()(const FuncNode & obj) const
    {
        return hash<string>()(obj.getId());
    }
};

struct FuncNodeComparator
{
    
    bool
    operator()(const FuncNode & obj1, const FuncNode & obj2) const
    {
        if (obj1.getId() == obj2.getId())
            return true;
        return false;
    }
};
