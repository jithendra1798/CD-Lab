/*Write a program to translate math expressions from infix to postfix notation using syntax-directed translation.*/
%{
#include"y.tab.h"
#include<stdio.h>
extern int yylval;
%}
%%
[0-9]+  {yylval=atoi(yytext); return NUM;}
\n      return 0;
.       return *yytext;
%%

int yywrap(){
    
    return 1;
}