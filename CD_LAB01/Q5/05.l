Write a lex program to replace the sequence of white spaces by a single blank from input.*/
%{
   
%}

space [ \n\t]
%%

{space}+ printf(" ");


%%

 int main()
{

    yylex();
   
    return 0;
    
}
int yywrap(){
	return 1;
}

