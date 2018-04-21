//
//  VarNode.hpp
//  CompilerTestProject
//
//  Created by Ruben Hidalgo on 3/8/18.
//  Copyright © 2018 Ruben Hidalgo. All rights reserved.
//

#ifndef VarNode_hpp
#define VarNode_hpp

#include <string>
#include <iostream>
#include <queue>
#include "Type.hpp"
#endif 

using namespace std;




class VarNode{
   private:
        string id;
        Type type;
        int memDir;
        queue<int> dimensions;
    
    
    public:

    VarNode( string identifier, Type dataType, int memoryDirection){
        id = identifier;
        type = dataType;
        memDir = memoryDirection;
    }

    VarNode( string identifier, Type dataType, int memoryDirection, queue<int> dimension){
        id = identifier;
        type = dataType;
        memDir = memoryDirection;
        dimensions = dimension;
    }
    
    string getId() const{
        return id;
    }

    int getMemDir() const{
        return memDir;
    }

    queue<int> getArrayInfo(){
        return dimensions;
    }

};


namespace std
{
    template<> struct hash<VarNode>
    {
        size_t
        operator()(const VarNode & obj) const
        {
            return hash<string>()(obj.getId());
        }
    };
    
}

struct VarNodeHasher
{
    size_t
    operator()(const VarNode & obj) const
    {
        return hash<string>()(obj.getId());
    }
};

struct VarNodeComparator
{

    bool
    operator()(const VarNode & obj1, const VarNode & obj2) const
    {
        if (obj1.getId() == obj2.getId())
            return true;
        return false;
    }
};


