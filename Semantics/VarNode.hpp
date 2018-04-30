#ifndef VarNode_hpp
#define VarNode_hpp

#include <string>
#include <iostream>
#include "Type.hpp"
#include "Dimension.hpp"
#endif 

using namespace std;




class VarNode{
   private:
        string id;
        Type type;
        int memDir;
        Dimension* dimensionInformation = new Dimension();
    
    public:

    VarNode( string identifier, Type dataType ){
        
        id = identifier;
        type = dataType;
        memDir = -1;
        
    }

    VarNode( string identifier, Type dataType, int memoryDirection ){
        
        id = identifier;
        type = dataType;
        memDir = memoryDirection;
        
    }

    VarNode( string identifier, Type dataType, int memoryDirection, Dimension* dimensionInfo ){
        
        id = identifier;
        type = dataType;
        memDir = memoryDirection;
        dimensionInformation = dimensionInfo;

    }
    
    string getId() const{
        return id;
    }

    int getMemDir() const{
        return memDir;
    }

    Dimension* getDimensions() const{
        return dimensionInformation;
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