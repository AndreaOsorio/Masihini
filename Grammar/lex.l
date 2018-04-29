%option noyywrap
%{
    #include "grammar.tab.h"
        #include <iostream>
            using namespace std;
%}


float_num          "-"?[0-9]+"."[0-9]+"f"
int_num            "-"?([0]|[1-9][0-9]*)
id                 [a-zA-Z][_a-zA-Z0-9]* 
whitespace         [\t\v\f ]
linefeed           \n


%%
"local"                     { return LOCAL; }
"true"                      {return TRUE;}
"false"                     {return FALSE;}
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



"&&"                        { return AND; }
"||"                        { return OR; }
"!"                         { return NOT; }
";"                         { return SEMICOLON; }
":"                         { return COLON; }
","                         { return COMMA; }
"return"                    { return RETURN; }
"static"                    { return STATIC; }
"run"                       { return RUN; }
"void"                      { return VOID; }

"speak" |
"accel" |
"jump"  |
"stop"  |
"rot"                       { yylval.stringValue = strdup(yytext); return SYSTEM_PREFIX; }

">"                        {return GT;}
"<"                        {return LT;}
"<="                       {return LE;}
">="                       {return GE;}
"=="                       { return EE; }
'(\\.|[^\\'])+'            { yylval.stringValue = strdup(yytext); return STRING; }

{float_num}                 { yylval.floatValue = atof(yytext); return FLOAT; }
{int_num}                   { yylval.intValue = atoi(yytext); return INT; }
{id}                        { yylval.stringValue = strdup(yytext); return ID; }


{whitespace}
{linefeed}                  ++yylineno;


%%