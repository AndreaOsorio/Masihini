%option noyywrap
%{
    #include "parser.tab.h"
%}

whitespace   [ \n\t\v\f]
linefeed    \n

%%

[0-9]+"."[0-9]+             { return FLOAT; }
([0]|[1-9][0-9]*)           { return INT; }
[a-zA-Z][_a-zA-Z0-9]*       { return ID; }
\"([^\\\"]|\\.)*\"          { return STRING; }
"true"                      { return TRUE; }
"false"                     { return FALSE; }
"if"                        { return IF; }
"else"                      { return ELSE; }
"while"                     { return WHILE; }
"var"                       { return VAR; }
"func"                      { return FUNC; }
"int"                       { return TYPE_INT; }
"float"                     { return TYPE_FLOAT; }
"boolean"                   { return TYPE_BOOLEAN; }
"string"                    { return TYPE_STRING; }
"{"                         { return L_BRACE; }
"}"                         { return R_BRACE; }
"("                         { return L_PARENTHESIS; }
")"                         { return R_PARENTHESIS; }
"["                         { return L_BRACKET; }
"]"                         { return R_BRACKET; }
"+"                         { return ADD; }
"-"                         { return SUBS; }
"*"                         { return MULT; }
"/"                         { return DIV; }
"="                         { return EQ; }
"!="                        { return NE; }
">"                         { return GT; }
"<"                         { return LT; }
"<="                        { return LE; }
">="                        { return GE; }
"=="                        { return COMPARE; }
"&"                         { return AND; }
"|"                         { return OR; }
"!"                         { return NOT; }
";"                         { return SEMICOLON; }
":"                         { return COLON; }
","                         { return COMMA; }
"return"                    { return RETURN; }
"static"                    { return STATIC; }
"run"                       { return RUN; }
"speak"                     { return SPEAK; }
"accel"                     { return ACCEL; }
"rot"                       { return ROT; }
"stop"                      { return STOP; }
"jump"                      { return JUMP; }
"void"                      { return VOID; }

{whitespace}
{linefeed}                  ++yylineno;

%%
