/*Write a lex program to print the copy of input.*/
%{//#include<stdio.h>
int lineCount=0,charCount=0;
%}

%%
\n lineCount++;
.  charCount++;
%%
int  main()
{
	yylex();
	printf("Number of lines %d\n",lineCount);
	printf("Char count %d\n",charCount);
	return 0;
	
}
int yywrap(){
	return 1;
}
