%{
    #include <math.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <iostream>
    #include <stack>
    #include <queue>
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
    void performSemanticsArrays();
    void getDimensions();
    void calculateArrayIndex();
    void getArrayValue();
    void performArrayAssignment();
    void populateArray();
    void performSystemFunction(Operator op);
    void manageMemoryVarCte(Type type, char value);
    void printQuads();
    void performReturn();
    void checkForReturn();
    void performParamAssignment();
    Type getTypeFromContext(int value);
    int getDimensionNumberFromContext(int value);


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
      int functionDimensions = 0;
      FuncNode *currentDeclaredFunction ;
      VarTable *globalSymbolTable = new VarTable();
      FuncDir *functionDirectory = new FuncDir();

      //Variables used for arrays management
      bool hasDimensions = false;
      bool isConstant = false;
      bool isDeclaring = false;
      int dimSize = 1; //for declaring arrays (R)
      int currentDimension = 0; //for indexing arrays
      int dimNum = 0; //# of dims in array
      int r = 0;
      queue <int> dimensions;
      string idArray = "";


      //Parameters used to assign memory to items;

      MemoryFrame *globalMemoryFrame = new MemoryFrame(1,5000);

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

/* UNIONS DEFINITION */
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
                                                      if(declarationState == GLOBAL_){
                                                            int memDir;
                                                            if (hasDimensions)
                                                            {
                                                                  memDir = globalMemoryFrame->declareArr(currentDeclaredtype, dimSize);
                                                                  callForLocalRedefinitionError(globalSymbolTable->insertNode(new VarNode($3, currentDeclaredtype, memDir, dimensions)));
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
                                                                  memDir = frame->declareArr(currentDeclaredtype, dimSize);
                                                                  callForLocalRedefinitionError(symbolTable->insertNode(new VarNode($3, currentDeclaredtype, memDir, dimensions)));
                                                            }
                                                            else{
                                                                  memDir = frame->declareValue(currentDeclaredtype);
                                                                  callForLocalRedefinitionError(symbolTable->insertNode(new VarNode($3, currentDeclaredtype, memDir))); 
                                                            }                                                            
                                                            callForGlobalRedefinitionError(globalSymbolTable->isContained($3, currentDeclaredtype));
                                                            
                                                      }
                                                      isDeclaring = false;
                                                      hasDimensions = false; 
                                                      queue<int> empty;
                                                      swap( dimensions, empty );
                                                      dimSize = 1;
                                                }
            ;

func_declaration : {declarationState = LOCAL_;} func func_declaration
                 | run
                 ;

func : FUNC VOID {currentDeclaredtype = VOID_;}  func_0 
     | FUNC type type_1 func_0
     ;

type_1 : L_BRACKET R_BRACKET { isDeclaring = true; hasDimensions = true; functionDimensions++; } type_1
       |
       ;

func_0 :    ID    {
                        //Function definition
                        currentDeclaredFunction = new FuncNode($1, currentDeclaredtype, functionDimensions,  new VarTable(), new MemoryFrame(globalMemoryOffset, localMemoryFrameSize));
                        callForLocalRedefinitionError(functionDirectory->insertNode(currentDeclaredFunction));
                        currentDeclaredFunction->setStartingInstruction(quadrupleSet.size());
                        functionDimensions = 0;
                        hasDimensions = false;
                        isDeclaring = false;
                  }


            L_PARENTHESIS func_1 R_PARENTHESIS local_declaration 
       ;

func_1 : ID COLON type type_1 {            
                              //Parameter definition                                             
                              MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
                              int memDir = frame->declareValue(currentDeclaredtype);
                              VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                              currentDeclaredFunction->addParameter(memDir);
                              if(hasDimensions){
                                    callForLocalRedefinitionError(symbolTable->insertNode(new VarNode($1, currentDeclaredtype, memDir, dimensions)));
                              }
                              else{
                                    callForLocalRedefinitionError( symbolTable->insertNode(new VarNode($1, currentDeclaredtype, memDir)));
                              }
                              isDeclaring = false;
                              hasDimensions = false; 
                              functionDimensions = 0;
                              queue<int> empty;
                              swap( dimensions, empty );
                              dimSize = 1;

                              callForGlobalRedefinitionError(globalSymbolTable->isContained($1, currentDeclaredtype));
                        }
         func_2 
       |
       ;

func_2 : COMMA ID COLON type type_1 {
                                    //Parameter definition
                                    MemoryFrame *frame = currentDeclaredFunction->getMemoryFrame();
                                    int memDir = frame->declareValue(currentDeclaredtype);
                                    VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
                                    currentDeclaredFunction->addParameter(memDir);
                                    if(hasDimensions){
                                          callForLocalRedefinitionError(symbolTable->insertNode(new VarNode($2, currentDeclaredtype, memDir, dimensions)));
                                    }
                                    else{
                                          callForLocalRedefinitionError( symbolTable->insertNode(new VarNode($2, currentDeclaredtype,memDir)));
                                    }
                                    isDeclaring = false;
                                    hasDimensions = false;
                                    functionDimensions = 0; 
                                    queue<int> empty;
                                    swap( dimensions, empty );
                                    dimSize = 1;
                                     
                                    callForGlobalRedefinitionError(globalSymbolTable->isContained($2, currentDeclaredtype));
                              } 
      func_2 
       |
       ;

local_declaration : declaration local_declaration
                  | block {checkForReturn(); quadrupleSet.push_back(new Quadruple(ENDPROC_,-1, -1, -1));}
                  ;

run : STATIC FUNC VOID RUN L_PARENTHESIS R_PARENTHESIS      {
                                                                  currentDeclaredFunction = new FuncNode("run", VOID_, 0, new VarTable(), new MemoryFrame(globalMemoryOffset, localMemoryFrameSize));
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
                              else{
                                    queue <int> temp = globalSymbolTable->getDimension($1);
                                    if(!temp.empty()){ idArray = $1; }
                              }
                        }
                        else{
                              queue <int> temp = symbolTable->getDimension($1);
                              if(!temp.empty()){ idArray = $1; }
                        }
                        stackOperand.push(memDir);
                  } 
             array EQ {stackOperator.push(EQ_);} expression
                                                            {
                                                                  if(stackOperator.empty() == false && stackOperator.top() == EQ_ ){
                                                                        stackOperator.pop();
                                                                        if(stackOperator.empty() == false && stackOperator.top() == ARR_){
                                                                              performArrayAssignment();
                                                                        }
                                                                        else{
                                                                              performSemanticsAssignment(); 
                                                                        }         
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
            L_PARENTHESIS{stackOperator.push(FAKE_BTTM_);} func_call_1 R_PARENTHESIS 
            {
                  stackOperator.pop();
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
                  {

                        string value($1);

                        if(!value.compare("speak"))
                        performSystemFunction(SPEAK_);

                        if(!value.compare("move"))
                        performSystemFunction(ACCEL_);

                        if(!value.compare("jump"))
                        performSystemFunction(JUMP_);

                        if(!value.compare("rot"))
                        performSystemFunction(ROT_);

                        if(!value.compare("stop"))
                        performSystemFunction(STOP_);

                  }
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

exp_1 : ADD  {stackOperator.push(ADD_);}  exp
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
                        else{
                              queue <int> temp = globalSymbolTable->getDimension($1);
                              if(!temp.empty()){ idArray = $1; stackOperator.push(FAKE_BTTM_); }
                        }
                  }
                  else{
                        queue <int> temp = symbolTable->getDimension($1);
                        if(!temp.empty()){ idArray = $1; stackOperator.push(FAKE_BTTM_); }
                  }
                  stackOperand.push(memDir);

             } array
        | INT     {     
                        if(hasDimensions)
                        {
                             isConstant = true;
                             if(isDeclaring)
                              {
                                    if($1 > 0)
                                    {
                                          dimensions.push($1);
                                          dimSize *= ($1 + 1);
                                    }
                                    else{
                                          callForTypeMismatchError("Mismatch error, index of array should be greater than 0");
                                    }
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


array : L_BRACKET {isConstant=false; hasDimensions = true;} expression 
            {
                  int expressionResult = stackOperand.top();
                  Type type = getTypeFromContext(expressionResult);
                  if(type == INTEGER_){
                        if(isDeclaring && !isConstant){
                              callForTypeMismatchError("Mismatch error, index of array is not an Integer constant");
                        }
                        else if(!isDeclaring){
                              if(!idArray.empty())
                              {
                                    getDimensions();
                              }
                              performSemanticsArrays();
                        }
                  }
                  else{
                        callForTypeMismatchError("Mismatch error, index of array is not an Integer");
                  }
            }
      
      R_BRACKET { if(hasDimensions && !isDeclaring && (currentDimension == dimNum)){calculateArrayIndex();}  isConstant = false; }
      array                                         
      |
      ;


type :  TYPE_STRING   {currentDeclaredtype = STRING_;}
      | TYPE_INT      {currentDeclaredtype = INTEGER_;}  
      | TYPE_FLOAT    {currentDeclaredtype = FLOAT_;}
      | TYPE_BOOLEAN  {currentDeclaredtype = BOOLEAN_;}
      ;

%%



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

      Operator op = stackOperator.top();
      stackOperator.pop();

      int rightOperand = stackOperand.top();
      Type rightType = getTypeFromContext(rightOperand);
      stackOperand.pop();
      
      int leftOperand = stackOperand.top();
      Type leftType = getTypeFromContext(leftOperand );
      stackOperand.pop();

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

            int dirArray = -1;
            if(stackOperator.empty() == false && stackOperator.top() == ARR_){
                  dirArray = 1;
                  stackOperator.pop(); //eliminate ARR_
                  stackOperand.pop(); //eliminate initialDir from stack
            }

            Type type = getTypeFromContext(operand);

            if(op == SPEAK_){
                  quadrupleSet.push_back(new Quadruple(SPEAK_, dirArray, -1, operand));
            }

            if(op == ACCEL_){
                  if(type == INTEGER_ || type == FLOAT_){
                        quadrupleSet.push_back(new Quadruple(ACCEL_, dirArray, -1, operand));
                  }else{
                        callForTypeMismatchError("\"move\" does not support this operation");    
                  }
            }

             if(op == ROT_){
                  if(type == INTEGER_ || type == FLOAT_){
                        quadrupleSet.push_back(new Quadruple(ROT_, dirArray, -1, operand));
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




}

void performReturn(){

      int result = stackOperand.top();
      stackOperand.pop();
      
      //Check type of return value
      Type resultType = getTypeFromContext(result);

      //Check if it has dimensions and how many
      if(!idArray.empty())
      {
            getDimensions();
            resultDimensions = dimNum;
            dimNum = 0;
      }

      //Check return type and # of dimensions of current function
      Type functionType = currentDeclaredFunction->getType();
      int dimensionNumber = currentDeclaredFunction->getDimensionNumber();
      string id = currentDeclaredFunction->getId();
      int index = functionDirectory->search(id);

      //Compare type and # of dimensions
      if((resultType == functionType) && (resultDimensions == dimensionNumber)){
            if(dimensionNumber == 0){
                  quadrupleSet.push_back(new Quadruple(RETURN_, 1, index, result));
            }
            else{
                  //Asignar al stack de return los resultados r veces ya que es el offset de la memoria
                  quadrupleSet.push_back(new Quadruple(RETURN_, r, index, result));     
                  r = 1;
            }

            FuncNode* func = functionDirectory->at(index);
            func->setReturnValue(memDir);
            func->setDimensionProperties(dimensionNumber, dimensions);
            queue<int> empty;
            swap( dimensions, empty );
            
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
      Type rightType = getTypeFromContext( rightOperand );
      stackOperand.pop();
      
      int leftOperand = stackOperand.top();
      Type leftType = getTypeFromContext( leftOperand );
      stackOperand.pop();

      Type resultType = semantics->isAllowed(rightType,leftType, EQ_);

      if(resultType == VOID_){
            callForTypeMismatchError("Mismatch error, cannot perform operation");                      
      }else{ 
            //Creating quadruple for action
            quadrupleSet.push_back(new Quadruple(EQ_, rightOperand, -1, leftOperand));
      }

}

void performArrayAssignment()
{

      MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

      int result = stackOperand.top();
      Type type = getTypeFromContext( result );
      stackOperand.pop();
      
      int tempDir = stackOperand.top();
      stackOperand.pop();

      //Init memory direction for semantics check
      int initialOperand = stackOperand.top();
      Type initialType = getTypeFromContext( initialOperand );
      stackOperand.pop();

      Type resultType = semantics->isAllowed(initialType, type, EQ_);

      if(resultType == VOID_){
            callForTypeMismatchError("Mismatch error, cannot perform operation");                      
      }else{ 
            //Creating quadruple for action
            quadrupleSet.push_back(new Quadruple(DIR_, result, -1, tempDir));
            stackOperator.pop(); //pop of ARR_
      }
}


void populateArray(){
      
}


void getArrayValue()
{

      MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

      Operator op = stackOperator.top();
      stackOperator.pop();

      int tempDir = stackOperand.top();
      stackOperand.pop();

      int initialDir = stackOperand.top();
      stackOperand.pop();

      Type type = getTypeFromContext(initialDir);

      int value = memFrame->declareValue(type);
      stackOperand.push(value);
                  
      quadrupleSet.push_back(new Quadruple(op, tempDir, -1, value));

      if(stackOperator.empty() == false && stackOperator.top() == FAKE_BTTM_){
            stackOperator.pop();
      }

}

void getDimensions(){

      //With the id of the array we get the dimensions information
      VarTable *symbolTable = currentDeclaredFunction->getSymbolTable();
      int memDir = symbolTable->search(idArray);
      if(memDir == -1){
            dimensions = globalSymbolTable->getDimension(idArray);
      }
      else{
            dimensions = symbolTable->getDimension(idArray);
      }
      idArray = "";
      queue<int> tempArray = dimensions;
      r = 1;
      currentDimension = 0;
      dimNum = dimensions.size();
      while(!tempArray.empty())
      {
            r *= (tempArray.front() + 1);
            tempArray.pop();
      }

}

void performSemanticsArrays()
{
      // array[index] expr
      int index = stackOperand.top();

      int sizeArray = dimensions.front();
      dimensions.pop();

      if(!dimensions.empty())
      {
            r = r / (sizeArray + 1); //CALCULATE CURRENT Mn
      }

      //Create VERIFY quadruple
      quadrupleSet.push_back(new Quadruple(VER_, index, 0, sizeArray));

      MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

      if(!dimensions.empty())
      {
            // multiply current index by the Mn
            int currentMn = memFrame->registerValue(r);
            
            //array[index] expr
            int index = stackOperand.top();
            stackOperand.pop();

            int result = memFrame->declareValue(INTEGER_);
            stackOperand.push(result);

            quadrupleSet.push_back(new Quadruple(MULT_, index, currentMn, result));
            

            if(currentDimension > 0)
            {
                  // This is the value we just calculated (index * Mn)
                  int newRes = stackOperand.top();
                  stackOperand.pop();

                  // This is the value of the previous (index * Mn)
                  int currentSum = stackOperand.top();
                  stackOperand.pop();

                  int suma = memFrame->declareValue(INTEGER_);
                  stackOperand.push(suma);
                  
                  quadrupleSet.push_back(new Quadruple(ADD_, currentSum, newRes, suma));
            }
      }
      currentDimension++;
      if(currentDimension > dimNum){
            callForTypeMismatchError("Array has no such dimensions");
      }


}


void calculateArrayIndex(){

      if(currentDimension < dimNum){
            callForTypeMismatchError("Array has no such dimensions");
      }

      MemoryFrame *memFrame = currentDeclaredFunction->getMemoryFrame();

      //When we reached the last dimension:
      if(dimNum > 1)
      {
            //Current arr[index]
            int index = stackOperand.top();
            stackOperand.pop();

            //Last addition of previous dimensions accumulated
            int currentSum = stackOperand.top();
            stackOperand.pop();

            //Result of the quadruple
            int suma = memFrame->declareValue(INTEGER_);
            stackOperand.push(suma);

            //Add dimensions
            quadrupleSet.push_back(new Quadruple(ADD_, currentSum, index, suma));
      }
      
      if(currentDimension == dimNum){
            // T
            int temp = stackOperand.top();
            stackOperand.pop();

            // dirBase(Array)
            int memBase = stackOperand.top(); //this is a memDir, not a direction
      
            //translate into direction with value
            int dirBase = memFrame->registerValue(memBase);

            // Resulting direction
            int newBase = memFrame->declareValue(INTEGER_);
            stackOperand.push(newBase);

            //Add T + dirBase(Array)
            quadrupleSet.push_back(new Quadruple(ADD_, temp, dirBase, newBase));

            //Set values to cero
            currentDimension = 0;
            dimNum = 0;
            r = 1;
            hasDimensions = false;

            if(!stackOperator.empty() && stackOperator.top() == FAKE_BTTM_){
                  stackOperator.push(ARR_);
                  getArrayValue();
            }
            else{
                  stackOperator.push(ARR_);
            }

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
      if(type == BOOLEAN_){
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

      VirtualMachine virtualMachin (&quadrupleSet, functionDirectory->getFuncList(), globalMemoryFrame, globalMemoryOffset);

}
