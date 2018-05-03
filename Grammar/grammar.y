%{
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <iostream>
    #include <stack>
    #include <vector>
    #include "Semantics/DimensionalDeclarationHelper.hpp"
    #include "VirtualMachine/VirtualMachine.hpp"
    #include "Semantics/Type.hpp"
    #include "Semantics/Dimension.hpp"

    using namespace std;
    int yylex ();
    void yyerror (char const *);
    void run();
    extern int yylineno;
      //Parameters used to store values in Func Directory
      VarTable *globalSymbolTable = new VarTable();
      FuncDir *functionDirectory = new FuncDir();
      //Parameters used to assign memory to items;
      MemoryFrame *globalMemoryFrame = new MemoryFrame(1,5000);
      //DeclarationHelper
      DeclarationHelper* declarationHelper = new DeclarationHelper(globalSymbolTable,functionDirectory,globalMemoryFrame);
      //Global Quadruple Vector
      vector<Quadruple*> quadrupleSet;
      //Semantic Validation Helper
      SemanticValidationHelper* semanticHelper = new SemanticValidationHelper(declarationHelper, &quadrupleSet);
      DimensionalDeclarationHelper* dimensionalDeclarationHelper = new DimensionalDeclarationHelper(declarationHelper, semanticHelper);
      
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
%token <stringValue>  SYSTEM_PREFIX
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



%start start


%%

/* Grammar Rules */

start : { quadrupleSet.push_back(new Quadruple(GOTO_,-1, -1, -1));} global_declaration

global_declaration : STATIC declaration global_declaration
                    | func_declaration
                    ;

declaration : VAR  ID COLON type {declarationHelper->switchDimensionalDeclarationState();   dimensionalDeclarationHelper->setIsDeclaring(true); } array {declarationHelper->switchDimensionalDeclarationState();} SEMICOLON 
                                                {     

                                                      //Variable declaration
                                                      string id_value($2);
                                                      declarationHelper->setDimensionInformation(semanticHelper->getDimensionDeclarationInfo());
                                                      declarationHelper->performVariableDeclaration(id_value, false);
                                                      semanticHelper->clearDimensionDeclarationInformation();
                                                      dimensionalDeclarationHelper->setIsDeclaring(false);
                                                }
            ;

func_declaration : {declarationHelper->setDeclarationStateToLocal();} func func_declaration
                 | run
                 ;

func : FUNC VOID {declarationHelper->setCurrentDeclaredType(VOID_); declarationHelper->setDimensionFunctionCounter(0);}  func_0 
     | FUNC type  {declarationHelper->setDimensionFunctionCounter(0);} type_1 func_0
     ;

type_1 : L_BRACKET R_BRACKET {declarationHelper->addDimensionFunctionCounter();} type_1
       |
       ;

func_0 :    ID    {
                        //Function Declaration
                        string id_value($1);
                        declarationHelper->performFunctionDeclaration(id_value);
                        declarationHelper->getCurrentDeclaredFunction()->setStartingInstruction(quadrupleSet.size());
                  }


            L_PARENTHESIS func_1 R_PARENTHESIS local_declaration 
       ;

func_1 : ID COLON type {declarationHelper->switchDimensionalDeclarationState(); dimensionalDeclarationHelper->setIsDeclaring(true);} array {declarationHelper->switchDimensionalDeclarationState();} 
                        {            
                              //Parameter definition                                             
                              string id_value($1);
                              declarationHelper->setDimensionInformation(semanticHelper->getDimensionDeclarationInfo());
                              declarationHelper->performVariableDeclaration(id_value, true);
                              semanticHelper->clearDimensionDeclarationInformation();
                              dimensionalDeclarationHelper->setIsDeclaring(false);
                        }
         func_2 
       |
       ;

func_2 : COMMA ID COLON type  {declarationHelper->switchDimensionalDeclarationState(); dimensionalDeclarationHelper->setIsDeclaring(true);} array {declarationHelper->switchDimensionalDeclarationState();}
                              
                              {
                                    //ParameterDefinition
                                    string id_value($2);
                                    declarationHelper->setDimensionInformation(semanticHelper->getDimensionDeclarationInfo());
                                    declarationHelper->performVariableDeclaration(id_value, true);
                                    semanticHelper->clearDimensionDeclarationInformation();
                                    dimensionalDeclarationHelper->setIsDeclaring(false);
                              } 
      func_2 
       |
       ;

local_declaration : declaration local_declaration
                  | block {quadrupleSet.push_back(new Quadruple(ENDPROC_,-1, -1, -1));}
                  ;

run : STATIC FUNC VOID {declarationHelper->setCurrentDeclaredType(VOID_);} RUN L_PARENTHESIS R_PARENTHESIS      {


                                                                  declarationHelper->setDeclarationStateToLocal();
                                                                  declarationHelper->performFunctionDeclaration("run");
                                                                  declarationHelper->getCurrentDeclaredFunction()->setStartingInstruction(quadrupleSet.size());
                                                                  quadrupleSet.at(0)->setResult(quadrupleSet.size());   
                                                            } 
      local_declaration {semanticHelper->check_return(); quadrupleSet.push_back(new Quadruple(ENDPROG_, -1, -1, -1)); run();}

    ;

block : L_BRACE block_1
      ;

block_1 : statement block_1
        | block_2
        ;

block_2 : RETURN expression SEMICOLON {semanticHelper->perform_return();}block_3
        | block_3
        ;

block_3 : R_BRACE
        ;

statement : assignment
          | cycle
          | condition
          | func_call SEMICOLON {semanticHelper->func_call_pop_result();}
          | system_func
          ;

assignment : ID {string value($1); semanticHelper->manage_var_cte_id(value);} array EQ {semanticHelper->pushOperator(EQ_);} expression {semanticHelper->assignment_semantics();} SEMICOLON
           ;

condition : IF L_PARENTHESIS expression R_PARENTHESIS {semanticHelper->conditional_semantics();} block condition_1
          ;

condition_1 : ELSE {semanticHelper->perform_else();} block {semanticHelper->conditional_close();}
            | {semanticHelper->conditional_close();}
            ;

func_call : ID { string value($1); semanticHelper->initialize_func_call(value);}L_PARENTHESIS {semanticHelper->pushOperator(FAKE_BTTM_);}func_call_1 R_PARENTHESIS {string value($1); semanticHelper->subscribe_func_call(value);}
          ;

func_call_1 :  expression {semanticHelper->param_assignment();} func_call_2
            |
            ;

func_call_2 : COMMA expression {semanticHelper->param_assignment();}  func_call_2
            |
            ;

system_func : SYSTEM_PREFIX L_PARENTHESIS system_func_1 R_PARENTHESIS SEMICOLON{string value($1); semanticHelper->system_func_semantics(value);}
            ;

system_func_1 : expression 
              |
              ;

cycle : WHILE {semanticHelper->pushPendingJumps(quadrupleSet.size());} 
            L_PARENTHESIS {semanticHelper->pushOperator(FAKE_BTTM_);} expression R_PARENTHESIS { semanticHelper->popFakeBottom(); semanticHelper->cycle_semantics();} block {semanticHelper->close_cycle();}
      ;


expression : NOT {semanticHelper->pushOperator(NOT_);}  relation {semanticHelper->not_semantics();} expression_1  {semanticHelper->boolean_semantics();}
           | relation expression_1 {semanticHelper->boolean_semantics();}
           ;

expression_1 : AND {semanticHelper->pushOperator(AND_);} expression_2
             | OR {semanticHelper->pushOperator(OR_);} expression_2
             |
             ;

expression_2 : NOT {semanticHelper->pushOperator(NOT_);} relation {semanticHelper->not_semantics();}
             | relation
             ;

relation : exp relation_1 {semanticHelper->relop_semantics();}
           ;

relation_1  : GT {semanticHelper->pushOperator(GT_);} exp
            | LT {semanticHelper->pushOperator(LT_);} exp
            | LE {semanticHelper->pushOperator(LE_);} exp
            | GE {semanticHelper->pushOperator(GE_);} exp
            | EE {semanticHelper->pushOperator(EE_);} exp
            |
            ;


exp : term {semanticHelper->add_subs_semantics();} exp_1
    ;

exp_1 : ADD {semanticHelper->pushOperator(ADD_);} exp
      | SUBS {semanticHelper->pushOperator(SUBS_);} exp
      |
      ;

term  : factor  {semanticHelper->mult_div_semantics();} term_1
      ;

term_1 : MULT {semanticHelper->pushOperator(MULT_);}  term
       | DIV {semanticHelper->pushOperator(DIV_);}  term
       |
       ;

factor : L_PARENTHESIS {semanticHelper->pushOperator(FAKE_BTTM_);}  expression R_PARENTHESIS  {semanticHelper->popFakeBottom();}
       | var_cte 
       ;



var_cte : func_call{int index = quadrupleSet.at(quadrupleSet.size()-1)->getResult() * -1; semanticHelper->func_call_as_exp();}
        | ID {string value($1); semanticHelper->manage_var_cte_id(value);} array
        | INT 
            {


              semanticHelper->manage_var_cte<int>($1);  
                  if($1>0 && declarationHelper->getdimensionalDeclarationState() == MULTIDIMENSIONAL_){
                        dimensionalDeclarationHelper->setIsConstant(true); 
                  }
                       
            }
        | FLOAT {semanticHelper->manage_var_cte<float>($1);}
        | STRING  {semanticHelper->manage_var_cte<string>($1);}
        | TRUE  {semanticHelper->manage_var_cte<bool>(true);} 
        | FALSE  {semanticHelper->manage_var_cte<bool>(false);}  
        ;


array : L_BRACKET {semanticHelper->pushFakeBottom();}
            expression 
            {
                  //Check that the expression is a constant and is greater than 0.
                  if(declarationHelper->getdimensionalDeclarationState() == MULTIDIMENSIONAL_){
                     
                       
                        dimensionalDeclarationHelper->verifyDeclaration();
                        dimensionalDeclarationHelper->setIsConstant(false);
                        semanticHelper->calculateArraySpace();
                        
                  }
                  if(dimensionalDeclarationHelper->getIsDeclaring() == false){ 


                        int currentDimension = semanticHelper->getCurrentDimension();
                        semanticHelper->addNewDimension(currentDimension + 1);
                        semanticHelper->performSemanticsArray();
                  }
            }
            
            R_BRACKET 
            {
                  semanticHelper->popFakeBottom();
                  if(dimensionalDeclarationHelper->getIsDeclaring() == false){ 
                        semanticHelper->calculateArrayIndex();
                  }
                  
            }

            array
      |
      ;


type :  TYPE_STRING     {declarationHelper->setCurrentDeclaredType(STRING_);}
      | TYPE_INT        { declarationHelper->setCurrentDeclaredType(INTEGER_);}  
      | TYPE_FLOAT      {declarationHelper->setCurrentDeclaredType(FLOAT_);}
      | TYPE_BOOLEAN    {declarationHelper->setCurrentDeclaredType(BOOLEAN_);}
      ;

%%





void yyerror(char const *x)
{

    cout <<yylineno<<" ERROR: "<<x<<endl;
    exit (0);
}

void run(){
      VirtualMachine virtualMachin(&quadrupleSet, functionDirectory->getFuncList(), globalMemoryFrame, declarationHelper->getGlobalOffset() );
}