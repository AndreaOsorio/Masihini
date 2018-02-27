%option noyywrap
%{
    #include "grammar.tab.h"
%}

float_num          [0-9]+"."[0-9]+
int_num            ([0]|[1-9][0-9]*)
id                 [a-zA-Z][_a-zA-Z0-9]*
string_literal      \"(([^\"]|\\\")*[^\\])?\"
whitespace         [\t\v\f ]
linefeed           \n


%%

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

{float_num}                 { return FLOAT; }
{int_num}                   { return INT; }
{id}                        { return ID; }
{string_literal}            { return STRING;}

{whitespace}
{linefeed}                  ++yylineno;


%%
