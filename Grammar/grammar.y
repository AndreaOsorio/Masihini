%{
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <iostream>
    #include <stack>
    #include <vector>
    #include "Semantics/FuncDir.hpp"
    #include "Memory/MemoryFrame.hpp"
    #include "Semantics/SemanticRuleSet.hpp"
    #include "Quadruples/Quadruple.hpp"
    #include "VirtualMachine/VirtualMachine.hpp"

    using namespace std;

    int yylex ();
    void yyerror (char const *);
    extern int yylineno;

    //Semantic functions
    void performSemantics();
    void performSemanticsNot();
    void performSemanticsAssignment();
    void manageMemoryVarCte(Type type, char value);
    void printQuads();
    void performReturn();
    void checkForReturn();
    void performParamAssignment();
    Type getTypeFromContext(int value);


    //Functions that handle errors

    void callForLocalRedefinitionError(string message);
    void callForGlobalRedefinitionError(string message);
    void callForNonDeclaredVariableError(string message);
    void callForTypeMismatchError(string message);

    //Functions used to run code
    void run();

      //Parameters used to store values in Func Directory
      DeclarationState declarationState = GLOBAL_;
      Type currentDeclaredtype = VOID_;
      FuncNode *currentDeclaredFunction ;
      VarTable *globalSymbolTable = new VarTable();
      FuncDir *functionDirectory = new FuncDir();

      //Parameters used to assign memory to items;

      MemoryFrame *globalMemoryFrame = new MemoryFrame(0,5000);

      //Stack used for Code Generation

      stack <int> stackOperand;
      stack <Operator> stackOperator;
      stack <int> pendingJumps;

      //Set of global semantic considerations
      SemanticRuleSet *semantics ;

      //Global Quadruple Vector
      vector<Quadruple*> quadrupleSet;

      //Parameter used to store functions being called
      FuncNode* currentCalledFunction;
      int parameterCounter;

      //Settings for memory management 

      int globalMemoryOffset = 25000;
      int localMemoryFrameSize = 10000;

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


%start start


%%

/* Grammar Rules */

start : { quadrupleSet.push_back(new Quadruple(GOTO_,-1, -1, -1));} global_declaration

global_declaration : STATIC declaration global_declaration 
                    | func_declaration
                    ;

declaration : VAR ID COLON type array SEMICOLON 
                                                { 
                                                      if(declarationState == GLOBAL_){
                                                            int memDir = globalMemoryFrame->declareValue(currentDeclaredtype);
                                                            callForLocalRedefinitionError(globalSymbolTable->insertNode(new VarNode($2, currentDeclaredtype, memDir))); 
                                                      }else{
                                                            MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
                                                            int memDir = frame->declareValue(currentDeclaredtype);
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
                        currentDeclaredFunction = new FuncNode($1, currentDeclaredtype, new VarTable(), new MemoryFrame(globalMemoryOffset, localMemoryFrameSize));
                        callForLocalRedefinitionError(functionDirectory->insertNode(currentDeclaredFunction));
                        currentDeclaredFunction->setStartingInstruction(quadrupleSet.size());
                  }


            L_PARENTHESIS func_1 R_PARENTHESIS local_declaration 
       ;

func_1 : ID COLON type {            
                              //Parameter definition                                             
                              MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
                              int memDir = frame->declareValue(currentDeclaredtype);
                              VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                              currentDeclaredFunction->addParameter(memDir);
                              callForLocalRedefinitionError( symbolTable->insertNode(new VarNode($1, currentDeclaredtype,memDir))); 
                              callForGlobalRedefinitionError(globalSymbolTable->isContained($1, currentDeclaredtype));
                        }
         func_2 
       |
       ;

func_2 : COMMA ID COLON type {
                                    //Parameter definition
                                    MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
                                    int memDir = frame->declareValue(currentDeclaredtype);
                                    VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                                    currentDeclaredFunction->addParameter(memDir);
                                    callForLocalRedefinitionError( symbolTable->insertNode(new VarNode($2, currentDeclaredtype,memDir))); 
                                    callForGlobalRedefinitionError(globalSymbolTable->isContained($2, currentDeclaredtype));
                              } 
      func_2 
       |
       ;

local_declaration : declaration local_declaration
                  | block {checkForReturn(); quadrupleSet.push_back(new Quadruple(ENDPROC_,-1, -1, -1));}
                  ;

run : STATIC FUNC VOID RUN L_PARENTHESIS R_PARENTHESIS      {
                                                                  currentDeclaredFunction = new FuncNode("run", VOID_, new VarTable(), new MemoryFrame(globalMemoryOffset, localMemoryFrameSize));
                                                                  callForLocalRedefinitionError(functionDirectory->insertNode(currentDeclaredFunction));
                                                                  currentDeclaredFunction->setStartingInstruction(quadrupleSet.size());
                                                                  quadrupleSet.at(0)->setResult(quadrupleSet.size());
                                                            } 
      local_declaration 
      {
            quadrupleSet.push_back(new Quadruple(ENDPROG_, -1, -1, -1));
            run();
      }
    ;

block : L_BRACE block_1
      ;

block_1 : statement block_1
        | block_2
        ;

block_2 : RETURN expression SEMICOLON {performReturn();}block_3
        | block_3
        ;

block_3 : R_BRACE
        ;

statement : assignment
          | cycle
          | condition
          | func_call SEMICOLON
          | system_func
          ;

assignment : ID 
                  {
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
                  } 
             array EQ {stackOperator.push(EQ_);} expression
                                                            {
                                                                  if(stackOperator.empty() == false && stackOperator.top() == EQ_ ){
                                                                        
                                                                        performSemanticsAssignment();
                                                                        
                                                                  }
                                                             }
             SEMICOLON
           ;

condition : IF L_PARENTHESIS expression R_PARENTHESIS {

      
                                                            int expressionResult = stackOperand.top();
                                                            Type type = getTypeFromContext(expressionResult);

                                                            if(type == BOOLEAN_){

                                                                  stackOperand.pop();
                                                                  quadrupleSet.push_back(new Quadruple(GOTOF_,expressionResult, -1, -1));
                                                                  pendingJumps.push(quadrupleSet.size()-1);                    
                                                            }else{                        
                                                                   callForTypeMismatchError("Mismatch error, cannot perform operation");  
                                                            }

                                                      } block condition_1
          ;

condition_1 : ELSE
                  {
                        int index = pendingJumps.top();
                        pendingJumps.pop();

                        quadrupleSet.at(index)->setResult(quadrupleSet.size()+1);

                        quadrupleSet.push_back(new Quadruple(GOTO_,-1, -1, -1));

                        pendingJumps.push(quadrupleSet.size()-1);

                  } 
                  block
                  {
                        int index = pendingJumps.top();
                        pendingJumps.pop();

                        quadrupleSet.at(index)->setResult(quadrupleSet.size());


                  }
            | 
            {
                  int index = pendingJumps.top();
                  pendingJumps.pop();
                  quadrupleSet.at(index)->setResult(quadrupleSet.size());

            }
            ;

func_call : ID
            {
                  string id ($1);
                  int result = functionDirectory->search(id);
                  if (result == -1){
                        string message;
                        message = "Function \"" + id + "\" "+"has not been declared";
                        callForNonDeclaredVariableError(message);
                  }else{

                        currentCalledFunction = functionDirectory->getFunc(result);
                        quadrupleSet.push_back(new Quadruple(ERA_,-1, -1, result));
                        parameterCounter = 0;

                  }
            }
            L_PARENTHESIS func_call_1 R_PARENTHESIS 
            {
                  string id ($1);
                  int result = functionDirectory->search(id);
                  int numberOfParameters = currentCalledFunction->getNumberOfParameters();
                  if (parameterCounter < numberOfParameters ){
                       callForTypeMismatchError("Missing parameters for call of function\"" + id + "\""); 
                  }else{
                      quadrupleSet.push_back(new Quadruple(GOSUB_,-1, -1, result)); 
                  }

            }
          ;
func_call_1 :  expression {performParamAssignment();}  func_call_2
            |
            ;

func_call_2 : COMMA expression {performParamAssignment();} func_call_2
            |
            ;

system_func : SYSTEM_PREFIX L_PARENTHESIS system_func_1 R_PARENTHESIS SEMICOLON
            ;

system_func_1 : expression 
              |
              ;

cycle : WHILE 
            {
                  pendingJumps.push(quadrupleSet.size());
            }
            L_PARENTHESIS expression R_PARENTHESIS
            {


                  int expressionResult = stackOperand.top();
                  Type type = getTypeFromContext(expressionResult);


                  if(type == BOOLEAN_){

                        stackOperand.pop();
                        quadrupleSet.push_back(new Quadruple(GOTOF_,expressionResult, -1, -1));
                        pendingJumps.push(quadrupleSet.size()-1);                    
                  }else{                        
                        
                        cout<<"my type is "<<type<<endl;
                              callForTypeMismatchError("Mismatch error, cannot perform operation");  
                  }

            } 
            block
            {

                        int index = pendingJumps.top();
                        pendingJumps.pop();
                        quadrupleSet.at(index)->setResult(quadrupleSet.size()+1);

                        index = pendingJumps.top();
                        pendingJumps.pop();
                        quadrupleSet.push_back(new Quadruple(GOTO_,-1, -1, index));
                  
            }
      ;


expression : NOT {stackOperator.push(NOT_);} relation {performSemanticsNot();}
             expression_1
                        {
                              if(stackOperator.empty() == false && (stackOperator.top() == AND_ || stackOperator.top() == OR_) ){
                                          performSemantics();
                              }
                        } 

           | relation expression_1 
                        {
                              if(stackOperator.empty() == false && (stackOperator.top() == AND_ || stackOperator.top() == OR_)){
                                    performSemantics();   
                              }
                        } 
           ;

expression_1 : AND {stackOperator.push(AND_);} expression_2
             | OR {stackOperator.push(OR_);} expression_2
             |
             ;

expression_2 : NOT {stackOperator.push(NOT_);} relation {performSemanticsNot();}
             | relation
             ;

relation : exp relation_1 
            {
                  if(stackOperator.empty() == false){
                        if(stackOperator.top() == GT_ || stackOperator.top() == LT_ ||stackOperator.top() == LE_ || stackOperator.top() == GE_ || stackOperator.top() == EE_ ){
                              performSemantics();
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


exp : term  
            {
                  if(stackOperator.empty() == false && ( stackOperator.top() == ADD_ || stackOperator.top() == SUBS_ )){
                        performSemantics();
                  }
            } 
      exp_1
    ;

exp_1 : ADD {stackOperator.push(ADD_);} exp
      | SUBS {stackOperator.push(SUBS_);} exp
      |
      ;

term  : factor
            {
                  if(stackOperator.empty() == false && (stackOperator.top() == MULT_ || stackOperator.top() == DIV_  )){
                        performSemantics();
                  }
            } 
            term_1
      ;

term_1 : MULT {stackOperator.push(MULT_);} term
       | DIV {stackOperator.push(DIV_);} term
       |
       ;

factor : L_PARENTHESIS {stackOperator.push(FAKE_BTTM_);}   expression R_PARENTHESIS  
            {
                  if (stackOperator.top() ==  FAKE_BTTM_)
                  stackOperator.pop();

            }
       | var_cte 
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
        | INT     {manageMemoryVarCte(INTEGER_, $1);}
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


array : L_BRACKET expression R_BRACKET array
      |
      ;


type :  TYPE_STRING     {currentDeclaredtype = STRING_;}
      | TYPE_INT        {currentDeclaredtype = INTEGER_;}  
      | TYPE_FLOAT      {currentDeclaredtype = FLOAT_;}
      | TYPE_BOOLEAN    {currentDeclaredtype = BOOLEAN_;}
      ;

%%

Type getTypeFromContext(int value){

      Type type;

      if(value<globalMemoryOffset){
            type = globalMemoryFrame->getType(value);

      }else{
            MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
            type = memFrame->getType(value);

      }

      return type;
}

void performSemantics(){
      MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();


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

void performReturn(){
      MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
      int result = stackOperand.top();
      Type resultType = getTypeFromContext(result);
      stackOperand.pop();

      Type functionType = currentDeclaredFunction->getType();

      if(resultType == functionType){
            quadrupleSet.push_back(new Quadruple(RETURN_, -1, -1, result));
      }else{
             callForTypeMismatchError("Return mismatch error, cannot perform operation"); 
      }

}

void checkForReturn(){
      Operator operator_ = quadrupleSet.at(quadrupleSet.size()-1)->getOperator();
      Type functionType = currentDeclaredFunction->getType();



      if(operator_ != RETURN_ && functionType != VOID_){
            string message;
            callForTypeMismatchError(" \"return\" statement is required at the end of function"); 
      }
}

void performParamAssignment(){

      int numberOfParameters = currentCalledFunction->getNumberOfParameters();
      string name = currentCalledFunction->getId();
      if(numberOfParameters==0){
            callForTypeMismatchError("No parameters expected in call of function \""+name+"\"" ); 
      }else{

            if(numberOfParameters==parameterCounter){
                  callForTypeMismatchError("Function \""+name+"\" requires " +to_string( numberOfParameters)+ " parameters"  ); 
            }else{
            
                  MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
                  int result = stackOperand.top();
                  Type resultType =getTypeFromContext(result);
                  stackOperand.pop();

                  Type parameterType = currentCalledFunction->getParameterType(parameterCounter);

                  if(parameterType==resultType){
                        quadrupleSet.push_back(new Quadruple(PARAMETER_, -1, result, parameterCounter));
                  }else{
                         callForTypeMismatchError("Parameter mismatch error, cannot perform operation"); 
                  }

                  parameterCounter++;

            }

      }

}

void performSemanticsAssignment(){

      MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

      int rightOperand = stackOperand.top();
      Type rightType = getTypeFromContext(rightOperand );
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
            //Creating quadruple for action
            quadrupleSet.push_back(new Quadruple(op, rightOperand, -1, leftOperand));
      }


}

void performSemanticsNot(){
      if(stackOperator.empty() == false){
            if(stackOperator.top() == NOT_){
                  MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

                  int rightOperand = stackOperand.top();
                  Type rightType = getTypeFromContext(rightOperand );
                  stackOperand.pop();
                                                                                   
                  int leftOperand = -1;
                  Type leftType = VOID_;

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
      }
}


void printQuads(){

      int count = 0;
      for ( auto &i : quadrupleSet ) {

            cout <<count<< ".- ";
            i->print();
            count++;
      }

}

void manageMemoryVarCte(Type type, char value){
      MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();
      int memDir;
      if(type == INTEGER_){
            memDir = memFrame->registerValue(value);
      }
      else if(type == BOOLEAN_){
            if(value == 1){
                  memDir = memFrame->registerValue(true);
            }else{
                  memDir = memFrame->registerValue(false);
            }
      }
      stackOperand.push(memDir);
}

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

void run(){

      VirtualMachine virtualMachin (&quadrupleSet, functionDirectory->getFuncList(), globalMemoryFrame);

}
