%{
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <iostream>
    #include <stack>
    #include <queue>
    #include <vector>
    #include "Semantics/SemanticValidationHelper.hpp"
    #include "VirtualMachine/VirtualMachine.hpp"
    #include "Semantics/ArrayInfo.hpp"
    

    using namespace std;

    int yylex ();
    void yyerror (char const *);
    void run();
    extern int yylineno;

      //Parameters used to store values in Func Directory
      VarTable *globalSymbolTable = new VarTable();
      FuncDir *functionDirectory = new FuncDir();

      //Parameters used for arrays management
      bool hasDimensions = false;
      bool isConstant = false;
      bool isDeclaring = false;
      int dimSize = 1;
      queue <int> dimensions;

      //Parameters used to assign memory to items;
      MemoryFrame *globalMemoryFrame = new MemoryFrame(1,5000);

      //DeclarationHelper
      DeclarationHelper* declarationHelper = new DeclarationHelper(globalSymbolTable,functionDirectory,globalMemoryFrame);

      //Global Quadruple Vector
      vector<Quadruple*> quadrupleSet;

      //Semantic Validation Helper
      SemanticValidationHelper* semanticHelper = new SemanticValidationHelper(declarationHelper, &quadrupleSet);



      

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

declaration : { isDeclaring = true; } VAR ID COLON type array SEMICOLON 
                                                { 
<<<<<<< HEAD
                                                      if(declarationState == GLOBAL_){
                                                            int memDir;
                                                            if (hasDimensions)
                                                            {
                                                                  memDir = globalMemoryFrame->declareArr(currentDeclaredtype, dimSize);
                                                                  callForLocalRedefinitionError(globalSymbolTable->insertNode(new VarNode($3, currentDeclaredtype, memDir, dimensions)));
                                                                  hasDimensions = false; 
                                                                  queue<int> empty;
                                                                  swap( dimensions, empty );
                                                                  dimSize = 1;
                                                            }
                                                            else{
                                                                  memDir = globalMemoryFrame->declareValue(currentDeclaredtype);
                                                                  callForLocalRedefinitionError(globalSymbolTable->insertNode(new VarNode($3, currentDeclaredtype, memDir))); 
                                                            }
                                                      }else{
                                                            MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
                                                            int memDir;
                                                            VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();

                                                            if (hasDimensions)
                                                            {
                                                                  memDir = globalMemoryFrame->declareArr(currentDeclaredtype, dimSize);
                                                                  callForLocalRedefinitionError(symbolTable->insertNode(new VarNode($3, currentDeclaredtype, memDir, dimensions)));
                                                                  hasDimensions = false;
                                                                  queue<int> empty;
                                                                  swap( dimensions, empty );
                                                                  dimSize = 1;
                                                            }
                                                            else{
                                                                  memDir = frame->declareValue(currentDeclaredtype);
                                                                  callForLocalRedefinitionError(globalSymbolTable->insertNode(new VarNode($3, currentDeclaredtype, memDir))); 
                                                            }                                                            
                                                            callForGlobalRedefinitionError(globalSymbolTable->isContained($3, currentDeclaredtype));
                                                            
                                                      }
                                                      isDeclaring = false;
=======
                                                      string id_value($2);
                                                      declarationHelper->performVariableDeclaration(id_value, false);
>>>>>>> c76dd181954fa270facde995331589b5e79d1df2
                                                }
            ;

func_declaration : {declarationHelper->setDeclarationStateToLocal();} func func_declaration
                 | run
                 ;

<<<<<<< HEAD
func : FUNC VOID {currentDeclaredtype = VOID_;}  func_0 
     | FUNC type type_1 func_0
=======
func : FUNC VOID {declarationHelper->setCurrentDeclaredType(VOID_);}  func_0 
     | FUNC type func_0
>>>>>>> c76dd181954fa270facde995331589b5e79d1df2
     ;

type_1 : L_BRACKET R_BRACKET type_1
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

func_1 : ID COLON type type_1 {            
                              //Parameter definition                                             
                              string id_value($1);
                              declarationHelper->performVariableDeclaration(id_value, true);
                        }
         func_2 
       |
       ;

<<<<<<< HEAD
func_2 : COMMA ID COLON type type_1 {
                                    //Parameter definition
                                    MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
                                    int memDir = frame->declareValue(currentDeclaredtype);
                                    VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                                    currentDeclaredFunction->addParameter(memDir);
                                    callForLocalRedefinitionError( symbolTable->insertNode(new VarNode($2, currentDeclaredtype,memDir))); 
                                    callForGlobalRedefinitionError(globalSymbolTable->isContained($2, currentDeclaredtype));
=======
func_2 : COMMA ID COLON type {
                                    //ParameterDefinition
                                    string id_value($2);
                                    declarationHelper->performVariableDeclaration(id_value, true);
>>>>>>> c76dd181954fa270facde995331589b5e79d1df2
                              } 
      func_2 
       |
       ;

local_declaration : declaration local_declaration
                  | block {quadrupleSet.push_back(new Quadruple(ENDPROC_,-1, -1, -1));}
                  ;

run : STATIC FUNC VOID {declarationHelper->setCurrentDeclaredType(VOID_);} RUN L_PARENTHESIS R_PARENTHESIS      {
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



<<<<<<< HEAD
var_cte : func_call{

                        int index = quadrupleSet.at(quadrupleSet.size()-1)->getResult() * -1;
                        stackOperand.push(index);


                  }
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
                        if(hasDimensions)
                        {
                             isConstant = true;
                             if(isDeclaring)
                              {
                                    dimensions.push($1);
                                    dimSize *= ($1 + 1);
                              }
                        }
                        int temp = $1;
                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                        int memDir = memFrame->registerValue(temp);
                        
                        
                        stackOperand.push(memDir);}
        | FLOAT   {
                        float temp = $1;
                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                        int memDir = memFrame->registerValue(temp);
                        stackOperand.push(memDir);
                   }
        | STRING  {
                        string literal($1);
                        MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                        int memDir = memFrame->registerValue(literal);
                        stackOperand.push(memDir);
                  }
        | TRUE    {manageMemoryVarCte(BOOLEAN_, 1);}
        | FALSE   {manageMemoryVarCte(BOOLEAN_, 0);}
        ;


array : L_BRACKET 
            
            {
                  hasDimensions = true; 
                  isConstant=false;
            }

      expression R_BRACKET

            {
                  int expressionResult = stackOperand.top();
                  Type type = getTypeFromContext(expressionResult);

                  if(type == INTEGER_){
                        if(isDeclaring && !isConstant){
                              callForTypeMismatchError("Mismatch error, index of array is not an Integer constant");
                        }
                        else{
                              if(!isConstant)
                              {
                                    VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                                    int memDir = symbolTable->search($2);
                                    if(memDir == -1){
                                          memDir = globalSymbolTable->search($2);
                                          if(memDir==-1){
                                                string id ($2);
                                                callForNonDeclaredVariableError("Variable \"" +id+ "\" has not been declared");
                                          }
                                    }
                              
                              }
                              else{
                                    
                              }
                              stackOperand.push(memDir); 
                              //quadrupleSet.push_back(new Quadruple(VERIFY_,memDir, 0, 0));    
                        }
                        isConstant = false;
                  }
                  else{
                        callForTypeMismatchError("Mismatch error, index of array is not an Integer constant");
                  }
                  /**
                  int value = stackOperand.top();
                  stackOperand.pop(); 
                  int lim = 0;
                  if(getTypeFromContext(value)==INTEGER_ && isConstant)
                  {
                        if (declarationState == GLOBAL_){
                              lim = globalMemoryFrame->getIntegerValue(value);
                        }else{
                              MemoryFrame* frame = currentDeclaredFunction->getMemoryFrame();
                              lim = frame->getIntegerValue(value);
                        }
                        
                        

                        isConstant = false;
                  }
                  */          
            }


      array  
                                              
=======
var_cte : func_call{int index = quadrupleSet.at(quadrupleSet.size()-1)->getResult() * -1; semanticHelper->func_call_as_exp();}
        | ID {string value($1); semanticHelper->manage_var_cte_id(value);} array
        | INT {semanticHelper->manage_var_cte<int>($1);}
        | FLOAT {semanticHelper->manage_var_cte<float>($1);}
        | STRING  {semanticHelper->manage_var_cte<string>($1);}
        | TRUE  {semanticHelper->manage_var_cte<bool>(true);} 
        | FALSE  {semanticHelper->manage_var_cte<bool>(false);}  
        ;


array : L_BRACKET expression R_BRACKET array
>>>>>>> c76dd181954fa270facde995331589b5e79d1df2
      |
      ;


<<<<<<< HEAD
type :  TYPE_STRING   {currentDeclaredtype = STRING_;}
      | TYPE_INT      {currentDeclaredtype = INTEGER_;}  
      | TYPE_FLOAT    {currentDeclaredtype = FLOAT_;}
      | TYPE_BOOLEAN  {currentDeclaredtype = BOOLEAN_;}
=======
type :  TYPE_STRING     {declarationHelper->setCurrentDeclaredType(STRING_);}
      | TYPE_INT        {declarationHelper->setCurrentDeclaredType(INTEGER_);}  
      | TYPE_FLOAT      {declarationHelper->setCurrentDeclaredType(FLOAT_);}
      | TYPE_BOOLEAN    {declarationHelper->setCurrentDeclaredType(BOOLEAN_);}
>>>>>>> c76dd181954fa270facde995331589b5e79d1df2
      ;

%%

<<<<<<< HEAD


Type getTypeFromContext(int value){

      Type type;


      if (value > 0){

            if(value<globalMemoryOffset){
                  type = globalMemoryFrame->getType(value);

            }else{
                  MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                  type = memFrame->getType(value);

            }

      }else{
            FuncNode* node = functionDirectory->getFuncList()->at(value*-1);
            type = node->getType();

      }


      return type;
}

void performSemantics(){

      MemoryFrame* memFrame = currentDeclaredFunction->getMemoryFrame();

      int rightOperand = stackOperand.top();
      Type rightType = getTypeFromContext(rightOperand);
      stackOperand.pop();
      
      int leftOperand = stackOperand.top();
      Type leftType = getTypeFromContext(leftOperand );
      stackOperand.pop();
      
      Operator op = stackOperator.top();
      stackOperator.pop();

      Type resultType = semantics->isAllowed(rightType,leftType, op);
      if(resultType == VOID_){
            callForTypeMismatchError("Mismatch error, cannot perform operation");                      
      }else{                        
            int result = memFrame->declareValue(resultType);
            stackOperand.push(result);

            //Creating quadruple for action
            quadrupleSet.push_back(new Quadruple(op, leftOperand, rightOperand, result));
      }

}

void performSystemFunction( Operator op){

      int operand;


      if(!stackOperand.empty())
      {
            operand = stackOperand.top();
            stackOperand.pop();
            Type type = getTypeFromContext(operand);

            if(op == SPEAK_){
                  quadrupleSet.push_back(new Quadruple(SPEAK_, -1, -1, operand));
            }

            if(op == ACCEL_){
                  if(type == INTEGER_ || type == FLOAT_){
                        quadrupleSet.push_back(new Quadruple(ACCEL_, -1, -1, operand));
                  }else{
                        callForTypeMismatchError("\"accel\" does not support this operation");    
                  }
            }

             if(op == ROT_){
                  if(type == INTEGER_ || type == FLOAT_){
                        quadrupleSet.push_back(new Quadruple(ROT_, -1, -1, operand));
                  }else{
                        callForTypeMismatchError("\"rot\" does not support this operation");    
                  }
            }

            if(op == STOP_ || op == JUMP_)
                  callForTypeMismatchError("This action does not call for a parameter");   

      }else{

            if(op == STOP_){
                  quadrupleSet.push_back(new Quadruple(STOP_, -1, -1, -1));
            }else if(op == JUMP_){
                  quadrupleSet.push_back(new Quadruple(JUMP_, -1, -1, -1));
            }else{
                  callForTypeMismatchError("This operation requires an expression");  
            }
     

      }


=======
>>>>>>> c76dd181954fa270facde995331589b5e79d1df2




void yyerror(char const *x)
{

    cout <<yylineno<<" ERROR: "<<x<<endl;
    exit (0);
}

void run(){
      VirtualMachine virtualMachin(&quadrupleSet, functionDirectory->getFuncList(), globalMemoryFrame, declarationHelper->getGlobalOffset() );
}

