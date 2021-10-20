
/*Lex program to print the copy of input.*/


%%
.   printf("%s",yytext);
%%
int main()
{
	yylex();
	return 0;
}
int yywrap()
{
	return 1;
}
