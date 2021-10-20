/*Write a lex program to replace ithe sequence of white spaces by a single blank from input
text file and add the contents in output text file.*/
%{
	/*definations*/
%}

%%
[ \n\t]+ {fprintf(yyout, " ");}
.	 { fprintf(yyout, "%s", yytext); }
%%
int yywrap(){
	return 1;
}
int main()
{	
	extern FILE *yyin,*yyout;
	yyin = fopen("input.txt", "r");
	yyout = fopen("output.txt", "w");
	yylex();
	return 0;
}
