%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex (void);
    void yyerror (char const *);
%}

/* TOKENS */

%token FLOAT
%token INT
%token ID
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
%token NE
%token GT
%token LT
%token LE
%token GE
%token COMPARE
%token AND
%token OR
%token NOT
%token SEMICOLON
%token COLON
%token COMMA
%token RETURN
%token STATIC
%token RUN
%token SPEAK
%token ACCEL
%token ROT
%token STOP
%token JUMP
%token VOID


%start global_declaration


%%

/* Grammar Rules */

global_declaration : global_declaration_1 run {;}
                   ;

global_declaration_1 : STATIC declaration global_declaration_1 {;}
                     | {;}
                     ;

run : FUNC VOID RUN L_PARENTHESIS R_PARENTHESIS block {;}
    ;

func : FUNC type func_1 {;}
     | FUNC VOID func_1 {;}
     ;

func_1 : ID L_PARENTHESIS func_2 {;}
       ;

func_2 : ID COLON type func_3 {;}
       ;

func_3 : COMMA func_2 {;}
       | R_PARENTHESIS block func {;}
       | R_PARENTHESIS block {;}
       ;

block  : L_BRACE block_1 {;}
       ;

block_1   : statement block_1 {;}
          | statement RETURN expression SEMICOLON R_BRACE {;}
          | statement R_BRACE {;}
          ;


type    :   TYPE_INT {;}
        |   TYPE_FLOAT {;}
        |   TYPE_BOOLEAN {;}
        |   TYPE_STRING {;}
        ;


expression : NOT relation expression_1 {;}
           | relation expression_1;

expression_1  :  AND expression_2{;}
              |  OR expression_2{;}
              |
              ;

expression_2 : NOT relation {;}
             | relation
             ;


relation : exp relation_1
         ;

relation_1 : GT relation_2 {;}
           | LT relation_2 {;}
           | GE relation_2 {;}
           | LE relation_2 {;}
           | NOT relation_2 {;}
           | {;}
           ;

relation_2 : exp {;}
          ;



statement : func_call SEMICOLON {;}
          | assignment {;}
          | condition {;}
          | declaration {;}
          | cycle {;}
          ;


cycle : WHILE L_PARENTHESIS expression  R_PARENTHESIS block {;}
      ;

condition : IF L_PARENTHESIS expression R_PARENTHESIS block condition_1 {;}
          ;

condition_1 : ELSE block SEMICOLON {;}
          | SEMICOLON {;}
          ;



declaration : VAR ID COLON type SEMICOLON {;}




func_call : system_func {;}
		  | ID L_PARENTHESIS func_call_1 {;}
		  ;

func_call_1 : expression func_call_2 {;}
				 | R_PARENTHESIS {;}
				 ;

func_call_2 : COMMA expression func_call_2 {;}
				  | R_PARENTHESIS {;}
				  ;


system_func : ACCEL system_func_1 {;}
			| ROT system_func_1 {;}
			| STOP system_func_1 {;}
			| JUMP system_func_1 {;}
			| SPEAK system_func_1 {;}
			;

system_func_1 : L_PARENTHESIS system_func_2 {;}
			  ;

system_func_2 : expression R_PARENTHESIS {;}
			  | R_PARENTHESIS {;}
			  ;


assignment : ID assignment_1 {;}
            ;
assignment_1 : L_BRACKET expression L_BRACKET assignment_2 {;}
			 | assignment_3 {;}
			 ;

assignment_2 : L_BRACKET expression R_BRACKET assignment_3 {;}
			 | assignment_3 {;}
			 ;

assignment_3 : expression {;}
			 ;



exp : term exp_1 {;}
    ;

exp_1 : ADD exp {;}
	  | SUBS exp {;}
	  | {;}
	  ;

term : factor term_1 {;}
     ;

term_1 : MULT term {;}
       | DIV term {;}
       | {;}
       ;


factor : L_PARENTHESIS expression R_PARENTHESIS {;}
	   | ADD factor_1 {;}
	   | SUBS factor_1 {;}
	   | factor_1{;}
	   ;

factor_1 : var_cte {;}
		 ;


var_cte : func_call {;}
		| INT {;}
		| FLOAT {;}
		| STRING {;}
		| FALSE {;}
		| TRUE {;}
		| ID {;}
		;



%%

void yyerror(char const *x)
{
    printf("Error %s\n", x);
    exit(1);
}
