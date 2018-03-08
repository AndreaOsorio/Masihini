#include <iostream>
#include "varTable.hpp"

extern "C"
{
  int yyparse();
  void yyerror(const char*);
  int yyparse();
}

int main()
{
  int result = yyparse();

  if(result){
    std::cout << "The input is valid. \n";
  }
  else
  {
    std::cout << "The input is valid.\n";
  }

  VarTable *varTable = new VarTable();

  return result;
}