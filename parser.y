%{
#include <stdio.h>
%}

%token NUMBER ID
%token IF ELSE FOR
%token TYPE
%token SEMICOLON
%token EQUAL_TO

%%

Goal:	Exprs '$' | '$' {printf("Rule accepted"); return 0;}

Exprs: Expr '\n' Exprs
	 | Expr '\t' Exprs
	 | Expr Exprs
     | Expr
     ;

Expr: assignment
	| operation
	| declaration
	;

operation: operation Op Term 
		 | Term
		 ;

declaration: TYPE ID SEMICOLON 
		 ;



assignment: ID EQUAL_TO operation 
		 ;

Term: NUMBER
	| ID
	;

Op:	'+'
	| '-'
	| '*'
	| '/'
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



