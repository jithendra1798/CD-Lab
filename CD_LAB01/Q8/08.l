%{
#include<stdio.h>
#include<stdlib.h>
int is_comment;
%}
letter      [a-zA-z]
digit       [0-9]
id          {letter}({letter}|{digit})*
numbers     {digit}+(.{digit}+)?(E[+-]?{digit}+)?
mult_div     [*/]
add_sub    [+-]
relational       ([<>=](=)?)|(!=)
delimiters  [{\(\)};,\[\]]
%%
#.*         { printf("%s is a preprocessing directive", yytext);}
if | 
endif | 
else | 
then | 
int         {printf("%s is a keyword\n", yytext);}
"/*"        {is_comment = 1;}
"*/"        {is_comment = 0;}
{id}        {if(!is_comment) printf("%s -> Identifier\n", yytext);}	
{numbers}     {if(!is_comment) printf("%s -> Constant\n", yytext);}
{relational}       {if(!is_comment) printf("%s -> Relational Operator\n", yytext);}
{add_sub}    {if(!is_comment) printf("%s -> Adding Operator\n", yytext);}
{mult_div}     {if(!is_comment) printf("%s -> Multiplication / Division Operator\n", yytext);}
\".*\"      {if(!is_comment) printf("%s -> String\n", yytext);}
{delimiters}  {if(!is_comment) printf("%s -> Delimiter\n", yytext);}
%%

int main(int argc, char *argv[]) {
    yyin = fopen("input2.txt", "r");
    yylex();
    fclose(yyin);
}
