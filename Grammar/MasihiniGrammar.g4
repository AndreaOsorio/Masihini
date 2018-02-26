grammar MasishiniGrammar;

/* GRAMMAR RULES */ 


global_declaration : global_declaration_1 RUN
                   ;

global_declaration_1 : STATIC declaration global_declaration_1
                     |
                     ;

run : FUNC VOID RUN PARENTHESIS_L PARENTHESIS_R block func
    ;

func : FUNC type func_1
     | FUNC VOID func_1
     ;

func_1 : ID PARENTHESIS_R func_2
       ;

func_3 : COMMA func_3
       | PARENTHESIS_R block func
       | PARENTHESIS_R block
       ;

block  : BRACE_L block_1
       ;

block_1   : statement block_1
          | statement RETURN expression SEMICOLON BRACKET_R
          | statement BRACKET_R
          ;

statement : func_call SEMICOLON
          | assignment
          | condition
          | declaration
          | cycle
          ;

func_call : system_func
          | ID PARENTHESIS_L expression func_call_1
          | ID PARENTHESIS_L PARENTHESIS_R
          ;

func_call_1 : COMMA expression func_call_1
            | PARENTHESIS_R








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
VOID : 'void';