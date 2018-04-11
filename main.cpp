
#include <iostream>


using namespace std;

extern int yyparse();
extern int yylineno;



int main()
{

  int result = yyparse();

    cout<< "BUILD IS SUCCESSFUL"<<endl;


  return result;
}