
#include <iostream>


#include "FuncDir.hpp"


extern int yyparse();
extern int yylineno;



int main()
{

/*
  VarNode *var  = new VarNode("hello", FLOAT_);
    
  VarNode *var2  = new VarNode("hello", FLOAT_);
  VarNode *var3  = new VarNode("hello1", FLOAT_);
  
  VarTable *table = new VarTable();
  
  table->insertNode(*var);
  table->insertNode(*var2);
  table->insertNode(*var3);
  
  FuncNode *node = new FuncNode("hello", VOID_, *table);
  FuncNode *node2 = new FuncNode("hello", VOID_, *table);

  FuncDir * dir = new FuncDir();
  
  dir->insertNode(*node);

*/
  int result = yyparse();

    cout<< "BUILD IS SUCESSFUL"<<endl;


  return result;
}