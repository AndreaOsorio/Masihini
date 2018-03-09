
#include <iostream>


#include "FuncDir.hpp"


extern int yyparse();
extern int yylineno;



int main()
{

  VarNode *var  = new VarNode("hello", FLOAT);
    
  VarNode *var2  = new VarNode("hello", FLOAT);
  VarNode *var3  = new VarNode("hello1", FLOAT);
  
  VarTable *table = new VarTable();
  
  table->insertNode(*var);
  table->insertNode(*var2);
  table->insertNode(*var3);
  
  FuncNode *node = new FuncNode("hello", VOID, *table);
  FuncNode *node2 = new FuncNode("hello", VOID, *table);

  FuncDir * dir = new FuncDir();
  
  dir->insertNode(*node);

  int result = yyparse();

  if(result){
    std::cout << "The input is valid. \n";
  }
  else
  {
    std::cout << "The input is valid.\n";
  }

  std::cout << "The number of lines in the file is: "<< yylineno <<std::endl;

  return result;
}