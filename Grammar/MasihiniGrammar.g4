grammar MasishiniGrammar;

/* GRAMMAR RULES */ 

global_declaration : _global declaration run
				   ;

global_declaration_lambda : STATIC declaration global_declaration_lambda
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
COMPARE : "=="
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