%{
#include <stdio.h>
%}

%token NUMBER ID
%token IF ELSE FOR
%token TYPE
%token SEMICOLON
%token EQUAL_TO
%token DOLLAR
%token OP UNARY_OP
%token FOR LEFT_BRACKET RIGHT_BRACKET 
%token FOR_SEPARATE
%%

Goal:	Exprs DOLLAR | DOLLAR {printf("Rule accepted"); return 0;}

Exprs: Expr '\n' Exprs
	 | Expr '\t' Exprs
	 | Expr Exprs
     | Expr
     ;

Expr: assignment
	| declaration
	| for_statement
	;

declaration: TYPE ID SEMICOLON 
		 ;

assignment: ID EQUAL_TO operation SEMICOLON
		 ;

operation: operation OP Term 
		 | Term 
		 | UNARY_OP Term 
		 ;

for_statement: FOR LEFT_BRACKET Term FOR_SEPARATE Term FOR_SEPARATE Term RIGHT_BRACKET

Term: NUMBER
	| ID
	;

%%

yyerror(char *s)
{
        fprintf(stderr, "error: %s\n", s);
}


main(int argc, char **argv)
{
        yyparse();
        printf("Parsing Over\n");
}



