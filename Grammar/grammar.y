%{
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <iostream>
    #include "FuncDir.hpp"

    using namespace std;

    int yylex ();
    void yyerror (char const *);

      DeclarationState declarationState = GLOBAL_;
      Type currentDeclaredtype = VOID_;
      string currrentDeclaredIdentificator;
      VarTable *globalSymbolTable = new VarTable();


%}

/*UNIONS DEFINITION*/

%union
{
    int intValue;
    float floatValue;
    char *stringValue;
    bool booleanValue;
}


/* TOKENS */

%token <floatValue>   FLOAT
%token <intValue>     INT
%token <stringValue>  ID
%token STRING
%token TRUE
%token FALSE
%token IF
%token ELSE
%token WHILE
%token VAR
%token FUNC
%token TYPE_INT
%token TYPE_FLOAT
%token TYPE_BOOLEAN
%token TYPE_STRING
%token L_BRACE
%token R_BRACE
%token L_PARENTHESIS
%token R_PARENTHESIS
%token L_BRACKET
%token R_BRACKET
%token ADD
%token SUBS
%token MULT
%token DIV
%token EQ
%token RELOP
%token AND
%token OR
%token NOT
%token SEMICOLON
%token COLON
%token COMMA
%token RETURN
%token STATIC
%token RUN
%token VOID
%token LOCAL
%token SYSTEM_PREFIX


%start global_declaration


%%

/* Grammar Rules */


global_declaration : STATIC declaration global_declaration  {
                                                                 declarationState = GLOBAL_;
                                                                
                                                            }
                    | func_declaration
                    ;

declaration : VAR ID COLON type array SEMICOLON { string identificator($2);
                                                currrentDeclaredIdentificator = identificator;
                                                if(declarationState == GLOBAL_){
                                                      globalSymbolTable->insertNode(*new VarNode(identificator, currentDeclaredtype));
                                                }}
            ;

func_declaration : func func_declaration 
                 | run
                 ;

func : FUNC VOID func_0 {currentDeclaredtype = VOID_}
     | FUNC type func_0
     ;

func_0 : ID L_PARENTHESIS func_1 R_PARENTHESIS local_declaration {}
       ;

func_1 : ID COLON type func_2
       |
       ;

func_2 : COMMA ID COLON type func_2
       |
       ;

local_declaration : declaration local_declaration
                  | block
                  ;

run : STATIC FUNC VOID RUN L_PARENTHESIS R_PARENTHESIS local_declaration
    ;

block : L_BRACE block_1
      ;

block_1 : statement block_1
        | block_2
        ;

block_2 : RETURN expression /* Aqui va Expression */ SEMICOLON block_2
        | R_BRACE
        ;


statement : assignment
          | cycle
          | condition
          | func_call SEMICOLON
          | system_func
          ;

assignment : ID array EQ expression /* Aqui va Expression */SEMICOLON
           ;

condition : IF L_PARENTHESIS expression /* Aqui va Expression */ R_PARENTHESIS block condition_1
          ;

condition_1 : ELSE block
            |
            ;

func_call : ID L_PARENTHESIS func_call_1 R_PARENTHESIS
          ;
func_call_1 :  expression /* Aqui va Expression */  func_call_2
            |
            ;

func_call_2 : COMMA expression /* Aqui va Expression */  func_call_2
            |
            ;

system_func : SYSTEM_PREFIX L_PARENTHESIS system_func_1 R_PARENTHESIS SEMICOLON
            ;

system_func_1 : expression /* Aqui va Expression */
              |
              ;

cycle : WHILE L_PARENTHESIS expression /* Aqui va Expression */ R_PARENTHESIS block
      ;


expression : NOT relation expression_1
           | relation expression_1
           ;

expression_1 : AND expression_2
             | OR expression_2
             |
             ;

expression_2 : NOT relation
             | relation
             ;

relation : exp relation_1
           ;

relation_1  : RELOP exp
              |
              ;


exp : term exp_1
    ;

exp_1 : ADD exp
      | SUBS exp
      |
      ;

term  : factor term_1
      ;

term_1 : MULT term
       | DIV term
       |
       ;

factor : L_PARENTHESIS expression R_PARENTHESIS
       | factor_1 var_cte 
       ;

factor_1 : ADD
         | SUBS
         |
         ;

var_cte : func_call
        | ID array
        | INT 
        | FLOAT 
        | STRING
        | TRUE
        | FALSE
        ;


array : L_BRACKET expression R_BRACKET array
      |
      ;


type :  TYPE_STRING     {currentDeclaredtype = STRING_;}
      | TYPE_INT        {currentDeclaredtype = INTEGER_;}  
      | TYPE_FLOAT      {currentDeclaredtype = FLOAT_;}
      | TYPE_BOOLEAN    {currentDeclaredtype = BOOLEAN_;}
      ;

%%

void yyerror(char const *x)
{
    printf("Error %s\n", x);
    exit(1);
}
