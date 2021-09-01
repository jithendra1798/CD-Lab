
/*definations*/
/*Write a lex program to print the copy of input.*/


%%
[.\n]	{;}
%%
int main()
{
	yylex();
	return 0;
}
