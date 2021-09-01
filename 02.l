digit [0-9]
letter [a-zA-Z]
letterordigit {letter}|{digit}
constant {digit}+
identifier {letter}{letterordigit}*
multop [\*\/]
addingop [\+\-]
relop (!=)|([<>=]=?)
comment (\/\*.*\*\/)|(\/\/.*)
keyword ["if""then""else""endif""print""while""do""enddo""int"]
delimeters [,;\[\]\(\)\{\}]


%{
#define IDENTIFIER 1 //constant values, variable names, function names,
#define KEYWORD 2 //reserved keywords like int for while etc
#define OPERATOR 3 //+ - * / == etc
#define SEPERATOR 4 //value seperators like , & ;
#define COMMENT 10 //comment
#define INVALID -1 //invalid sets in language
%}

%option nounput yylineno

%%

{identifier}      return IDENTIFIER;
{constant}      return IDENTIFIER;
{relop}         return OPERATOR;
{addingop}      return OPERATOR;
{multop}        return OPERATOR;
{comment}         return COMMENT;
{keyword}+        return KEYWORD;
{delimeters}      return SEPERATOR;
[ \t\n]+          ; 
.                return INVALID;

%%
extern int yylex();
extern int yylineno;
extern char *yytext;

int main()
{
    int comments = 0, tokens = 0, flag = 0;
    int n_token;
    n_token = yylex();
    // char *tokens[];
    while(n_token)
    {
        switch(n_token){
            case 1:
            case 2:
            case 3:
            case 4:
                tokens++;
                printf("%d %s\t", tokens, yytext);
                break;
            case 10:
                comments++;
                break;
            case -1:
                flag = 1;
                printf("\nSyntax Error: Invalid token in line no %d near %s\n",yylineno, yytext);
                break;
            default: 
                flag = 1;
                printf("\nCannot identify %s at line %d\n",yytext, yylineno);
        }

        n_token = yylex();
    }
    if(flag)
    {
        printf("\n\nPlease correct the errors\n");
    }
    else
    {
        printf("\n\nLexical Analyser SUMMARY: There are %d tokens and %d comments in the input file\n",tokens,comments);
    }
    return 0;
}
int yywrap(){
    return 1;
}
//c file will be declared as another file
