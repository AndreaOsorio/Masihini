grammar MasishiniGrammar;

/* GRAMMAR RULES */ 

global_declaration : _global declaration run
				   ;

global_declaration_1 : STATIC declaration global_declaration_1
						  |
						  ;



func_call : system_func
		  | ID PARENTHESIS_L func_call_1
		  ;

func_call_1 : expression func_call_2
				 | PARENTHESIS_R
				 ;

func_call_2 : COMMA expression func_call_2
				  | PARENTHESIS_R
				  ;


system_func : ACCEL system_func_1
			| ROT system_func_1
			| STOP system_func_1
			| JUMP system_func_1
			| SPEAK system_func_1
			;

system_func_1 : PARENTHESIS_R system_func_2
			  ;

system_func_2 : expression PARENTHESIS_R
			  | PARENTHESIS_R
			  ;


assignment : id assignment_1

assignment_1 : BRACKET_L expression BRACKET_R assignment_2 
			 | assignment_3
			 ;
			
assignment_2 : BRACKET_L expression BRACKET_R assignment_3 
			 | assignment_3
			 ; 

assignment_3 : expression
			 ;



exp : term exp_1

exp_1 : ADD exp
	  | SUBS exp
	  |
	  ;


factor : PARENTHESIS_L relation PARENTHESIS_R
	   | ADD factor_1
	   | SUBS factor_1
	   |
	   ;

factor_1 : var_cte
		 ;


var_cte : func_call
		| INT
		| FLOAT
		| STRING
		| FALSE
		| TRUE
		| ID var_cte_1
		;

var_cte_1 : BRACKET_L expression BRACKET_R var_cte_2
		  | var_cte_2
		  ;

var_cte_2 : BRACKET_L expression BRACKET_R
		  |
		  ;








/* TOKENS */

fragment ESCAPED_QUOTE : '\\"';
FLOAT : [0-9]+'.'[0-9]+ ;
INT : ([0]|[1-9][0-9]*) ;
ID : [a-zA-Z][_a-zA-Z0-9]*;
STRING : [a-zA-Z0-9]*;
TRUE : 'true';
FALSE : 'false';
IF : 'if';
ELSE : 'else';
WHILE : 'while';
VAR : 'var';
FUNC : 'func';
TYPE_INT : 'int';
TYPE_FLOAT : 'float';
TYPE_BOOLEAN : 'boolean';
TYPE_STRING : 'string';
BRACE_L : '{';
BRACE_R : '}';
PARENTHESIS_L : '(';
PARENTHESIS_R : ')';
BRACKET_L : '[';
BRACKET_R : ']';
ADD : '+';
SUBS : '-';
MULT : '*';
DIV : '/';
EQ : '=';
NE : '!=';
GT : '>';
LT : '<';
LE : '<=';
GE : '>=';
COMPARE : '==';
AND : '&';
OR : '|';
NOT : '!';
SEMICOLON : ';';
COLON : ':';
COMMA : ',';
RETURN : 'return';
STATIC : 'static';
RUN : 'run';
SPEAK : 'speak';
ACCEL : 'accel';
ROT : 'rot';
STOP : 'stop';
JUMP : 'jump';
STRING_LITERAL  :  '"' ( ESCAPED_QUOTE | ~('\n'|'\r') )*? '"';
WS          :   [ \n\t\r]+ -> skip;