%{
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <iostream>
    #include <stack>
    #include "FuncDir.hpp"
    #include "MemoryFrame.hpp"
    #include "SemanticRuleSet.hpp"

    using namespace std;

    int yylex ();
    void yyerror (char const *);
    extern int yylineno;



    //Functions that handle errors

    void callForLocalRedefinitionError(string message);
    void callForGlobalRedefinitionError(string message);
    void callForNonDeclaredVariableError(string message);
    void callForTypeMismatchError(string message);

      //Parameters used to store values in Func Directory
      DeclarationState declarationState = GLOBAL_;
      Type currentDeclaredtype = VOID_;
      FuncNode *currentDeclaredFunction ;
      VarTable *globalSymbolTable = new VarTable();
      FuncDir *functionDirectory = new FuncDir();

      //Parameters used to assign memory to items;

      MemoryFrame *globalMemoryFrame = new MemoryFrame();

      //Stack used for Code Generation

      stack <int> stackOperand;
      stack <Operator> stackOperator;

      //Set of global semantic considerations
      SemanticRuleSet *semantics ;
      

%}

/*UNIONS DEFINITION*/

%union
{
    int intValue;
    float floatValue;
    char *stringValue;
}


/* TOKENS */

%token <floatValue>   FLOAT
%token <intValue>     INT
%token <stringValue>  ID
%token <stringValue>  STRING
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
%token GT
%token LT
%token LE
%token GE
%token EE
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
                    |  func_declaration
                    ;

declaration : VAR ID COLON type array SEMICOLON { 
                                                      if(declarationState == GLOBAL_){
                                                            int memDir = globalMemoryFrame->declareValue(currentDeclaredtype);
                                                            callForLocalRedefinitionError(globalSymbolTable->insertNode(new VarNode($2, currentDeclaredtype, memDir))); 


                                                      }else{
                                                            int memDir = globalMemoryFrame->declareValue(currentDeclaredtype);
                                                            VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                                                            callForLocalRedefinitionError(symbolTable->insertNode(new VarNode($2, currentDeclaredtype, memDir))); 
                                                            callForGlobalRedefinitionError(globalSymbolTable->isContained($2, currentDeclaredtype));

                                                      }
                                                      
                                                      

                                                }
            ;

func_declaration : {declarationState = LOCAL_;} func func_declaration
                 | run
                 ;

func : FUNC VOID {currentDeclaredtype = VOID_;}  func_0 
     | FUNC type func_0
     ;

func_0 :    ID    {
                        //Function definition
                        currentDeclaredFunction = new FuncNode($1, currentDeclaredtype, new VarTable(), new MemoryFrame());
                        callForLocalRedefinitionError(functionDirectory->insertNode(currentDeclaredFunction));
                  }


            L_PARENTHESIS func_1 R_PARENTHESIS local_declaration 
       ;

func_1 : ID COLON type {
                              int memDir = globalMemoryFrame->declareValue(currentDeclaredtype);
                              VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                              callForLocalRedefinitionError( symbolTable->insertNode(new VarNode($1, currentDeclaredtype,memDir))); 
                              callForGlobalRedefinitionError(globalSymbolTable->isContained($1, currentDeclaredtype));
                              
                        } 
         
         
      func_2 
       |
       ;

func_2 : COMMA ID COLON type {
                                    int memDir = globalMemoryFrame->declareValue(currentDeclaredtype);
                                    VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                                    callForLocalRedefinitionError(symbolTable->insertNode(new VarNode($2, currentDeclaredtype,memDir))); 
                                    
                              } 
      func_2 
       |
       ;

local_declaration : declaration local_declaration
                  | block
                  ;

run : STATIC FUNC VOID RUN L_PARENTHESIS R_PARENTHESIS      {
                                                                  currentDeclaredFunction = new FuncNode("run", VOID_, new VarTable(), new MemoryFrame());
                                                                  callForLocalRedefinitionError(functionDirectory->insertNode(currentDeclaredFunction));

                                                            } 
      local_declaration
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

system_func_1 : expression 
              |
              ;

cycle : WHILE L_PARENTHESIS expression R_PARENTHESIS block
      ;


expression : NOT {stackOperator.push(NOT_);} relation{
                                                            if(stackOperator.empty() == false){
                                                                  if(stackOperator.top() == NOT_){
                                                                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

                                                                                    int rightOperand = stackOperand.top();
                                                                                    Type rightType = memFrame->getType(rightOperand);
                                                                                    stackOperand.pop();
                                                                                   
                                                                                    int leftOperand = 0;
                                                                                    Type leftType = VOID_;

                                                                                    Operator op = stackOperator.top();
                                                                                    stackOperator.pop();

                                                                                    Type resultType = semantics->isAllowed(rightType,leftType, op);
                                                                              if(resultType == VOID_){

                                                                                    callForTypeMismatchError("Mismatch error, cannot perform operation");
                                                                                    
                                                                              }else{
                                                                                    
                                                                                          int result = memFrame->declareValue(resultType);
                                                                                          stackOperand.push(result);
                                                                                          cout << "Right " << rightOperand<< " ";
                                                                                          cout << " RightType "<< rightType<<" ";
                                                                                          cout << "Left " << leftOperand<<"  ";
                                                                                          cout << " LefType "<< leftType<<endl;

                                                                              }

                                                                        

                                                                  }

                                                            }
                                                             

                                                      }

                                            expression_1{

                                                            if(stackOperator.empty() == false){
                                                                  if(stackOperator.top() == AND || OR_){
                                                                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

                                                                                    int rightOperand = stackOperand.top();
                                                                                    Type rightType = memFrame->getType(rightOperand);
                                                                                    stackOperand.pop();
                                                                                    int leftOperand = stackOperand.top();
                                                                                    Type leftType = memFrame->getType(leftOperand);
                                                                                    stackOperand.pop();
                                                                                    Operator op = stackOperator.top();
                                                                                    stackOperator.pop();

                                                                                    Type resultType = semantics->isAllowed(rightType,leftType, op);
                                                                              if(resultType == VOID_){

                                                                                    callForTypeMismatchError("Mismatch error, cannot perform operation");
                                                                                    
                                                                              }else{
                                                                                    
                                                                                          int result = memFrame->declareValue(resultType);
                                                                                          stackOperand.push(result);
                                                                                          cout << "Right " << rightOperand<< " ";
                                                                                          cout << " RightType "<< rightType<<" ";
                                                                                          cout << "Left " << leftOperand<<"  ";
                                                                                          cout << " LefType "<< leftType<<endl;

                                                                              }

                                                                        

                                                                  }

                                                                  }
                                                            } 
           | relation expression_1 {

                                    if(stackOperator.empty() == false){
                                          if(stackOperator.top() == AND || OR_){
                                                MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

                                                            int rightOperand = stackOperand.top();
                                                            Type rightType = memFrame->getType(rightOperand);
                                                            stackOperand.pop();
                                                            int leftOperand = stackOperand.top();
                                                            Type leftType = memFrame->getType(leftOperand);
                                                            stackOperand.pop();
                                                            Operator op = stackOperator.top();
                                                            stackOperator.pop();

                                                            Type resultType = semantics->isAllowed(rightType,leftType, op);
                                                      if(resultType == VOID_){

                                                            callForTypeMismatchError("Mismatch error, cannot perform operation");
                                                            
                                                      }else{
                                                            
                                                                  int result = memFrame->declareValue(resultType);
                                                                  stackOperand.push(result);
                                                                  cout << "Right " << rightOperand<< " ";
                                                                  cout << " RightType "<< rightType<<" ";
                                                                  cout << "Left " << leftOperand<<"  ";
                                                                  cout << " LefType "<< leftType<<endl;

                                                      }

                                                

                                          }

                              }
                        } 
           ;

expression_1 : AND {stackOperator.push(AND_);} expression_2
             | OR {stackOperator.push(OR_);} expression_2
             |
             ;

expression_2 : NOT {stackOperator.push(NOT_);} relation{
                                                            if(stackOperator.empty() == false){
                                                                  if(stackOperator.top() == NOT_){
                                                                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

                                                                                    int rightOperand = stackOperand.top();
                                                                                    Type rightType = memFrame->getType(rightOperand);
                                                                                    stackOperand.pop();
                                                                                   
                                                                                    int leftOperand = 0;
                                                                                    Type leftType = VOID_;

                                                                                    Operator op = stackOperator.top();
                                                                                    stackOperator.pop();

                                                                                    Type resultType = semantics->isAllowed(rightType,leftType, op);
                                                                              if(resultType == VOID_){

                                                                                    callForTypeMismatchError("Mismatch error, cannot perform operation");
                                                                                    
                                                                              }else{
                                                                                    
                                                                                          int result = memFrame->declareValue(resultType);
                                                                                          stackOperand.push(result);
                                                                                          cout << "Right " << rightOperand<< " ";
                                                                                          cout << " RightType "<< rightType<<" ";
                                                                                          cout << "Left " << leftOperand<<"  ";
                                                                                          cout << " LefType "<< leftType<<endl;

                                                                              }

                                                                        

                                                                  }

                                                            }
                                                             

                                                      }
             | relation
             ;

relation : exp relation_1 {

                  if(stackOperator.empty() == false){
                        if(stackOperator.top() == GT_ || stackOperator.top() == LT_ ||stackOperator.top() == LE_ || stackOperator.top() == GE_ || stackOperator.top() == EE_ ){
                              MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

                              int rightOperand = stackOperand.top();
                              Type rightType = memFrame->getType(rightOperand);
                              stackOperand.pop();
                              int leftOperand = stackOperand.top();
                              Type leftType = memFrame->getType(leftOperand);
                              stackOperand.pop();
                              Operator op = stackOperator.top();
                              stackOperator.pop();

                              Type resultType = semantics->isAllowed(rightType,leftType, op);
                             if(resultType == VOID_){

                                   callForTypeMismatchError("Mismatch error, cannot perform operation");
                                   
                             }else{
                              
                                    int result = memFrame->declareValue(resultType);
                                    stackOperand.push(result);
                                    cout << "Right " << rightOperand<< " ";
                                    cout << " RightType "<< rightType<<" ";
                                    cout << "Left " << leftOperand<<"  ";
                                    cout << " LefType "<< leftType<<endl;

                             }

                        }

                  }


                 

            } 
           ;

relation_1  : GT {stackOperator.push(GT_);} exp
            | LT {stackOperator.push(LT_);} exp
            | LE {stackOperator.push(LE_);} exp
            | GE {stackOperator.push(GE_);} exp
            | EE {stackOperator.push(EE_);} exp
            |
            ;


exp : term  {

                  if(stackOperator.empty() == false){
                        if(stackOperator.top() == ADD_ || stackOperator.top() == SUBS_  ){
                              MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

                              int rightOperand = stackOperand.top();
                              Type rightType = memFrame->getType(rightOperand);
                              stackOperand.pop();
                              int leftOperand = stackOperand.top();
                              Type leftType = memFrame->getType(leftOperand);
                              stackOperand.pop();
                              Operator op = stackOperator.top();
                              stackOperator.pop();

                              Type resultType = semantics->isAllowed(rightType,leftType, op);
                             if(resultType == VOID_){

                                   callForTypeMismatchError("Mismatch error, cannot perform operation");
                                   
                             }else{
                              
                                    int result = memFrame->declareValue(resultType);
                                    stackOperand.push(result);
                                    cout << "Right " << rightOperand<< " ";
                                    cout << " RightType "<< rightType<<" ";
                                    cout << "Left " << leftOperand<<"  ";
                                    cout << " LefType "<< leftType<<endl;

                             }

                        }

                  }


                 

            } 
      exp_1
    ;

exp_1 : ADD {stackOperator.push(ADD_);} exp
      | SUBS {stackOperator.push(SUBS_);} exp
      |
      ;

term  : factor {

                  if(stackOperator.empty() == false){
                        if(stackOperator.top() == MULT_ || stackOperator.top() == DIV_  ){
                              MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

                              int rightOperand = stackOperand.top();
                              Type rightType = memFrame->getType(rightOperand);
                              stackOperand.pop();
                              int leftOperand = stackOperand.top();
                              Type leftType = memFrame->getType(leftOperand);
                              stackOperand.pop();
                              Operator op = stackOperator.top();
                              stackOperator.pop();

                              Type resultType = semantics->isAllowed(rightType,leftType, op);
                             if(resultType == VOID_){

                                   callForTypeMismatchError("Mismatch error, cannot perform operation");
                                   
                             }else{
                              
                                    int result = memFrame->declareValue(resultType);
                                    stackOperand.push(result);
                                    cout << "Right " << rightOperand<< " ";
                                    cout << " RightType "<< rightType<<" ";
                                    cout << "Left " << leftOperand<<"  ";
                                    cout << " LefType "<< leftType<<endl;

                             }

                        }

                  }


                 

            } 
            term_1
      ;

term_1 : MULT {stackOperator.push(MULT_);} term
       | DIV {stackOperator.push(DIV_);} term
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
        | ID {
                  VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                  int memDir = symbolTable->search($1);
                  if(memDir == -1){
                        memDir = globalSymbolTable->search($1);
                        if(memDir==-1){
                              string id ($1);
                              callForNonDeclaredVariableError("Variable \"" +id+ "\" has not been declared");
                        }
                  }

                  stackOperand.push(memDir);

             } array
        | INT     {
                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                        int memDir = memFrame->registerValue($1);

                        stackOperand.push(memDir);
                  }
        | FLOAT  {
                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                        int memDir = memFrame->registerValue($1);

                        stackOperand.push(memDir);
                  }
        | STRING {
                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                        int memDir = memFrame->registerValue($1);

                        stackOperand.push(memDir);
                  }
        | TRUE    {
                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                        int memDir = memFrame->registerValue(true);

                        stackOperand.push(memDir);
                  }
        | FALSE  {
                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                        int memDir = memFrame->registerValue(false);

                        stackOperand.push(memDir);
                  }
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


void callForTypeMismatchError(string message){
      if(!message.empty()){
            cout<<yylineno<<" ERROR: "<<message << endl;
            exit (0);
      }
}

void callForNonDeclaredVariableError(string message){
      if(!message.empty()){
            cout<<yylineno<<" ERROR: "<<message << endl;
            exit (0);
      }
}


void callForLocalRedefinitionError(string message){
      if(!message.empty()){
            cout<<yylineno<<" ERROR: "<<message << endl;
            exit (0);
      }
}

void callForGlobalRedefinitionError(string message){
     
      if(!message.empty()){
                  cout<<yylineno<<" ERROR: "<<message << endl;
                  exit (0);
      }

}

void yyerror(char const *x)
{

    cout <<yylineno<<" ERROR: "<<x<<endl;
    exit (0);
}
