%{
#include <stdio.h>
%}

%token NUMBER ID

%%

Goal:	Exprs '$' | '$' {printf("Rule accepted"); return 0;}

Exprs: Expr '\n' Exprs
     | Expr
     ;

Expr: 	Expr Op Term
	| Term
	;

Term:	NUMBER
	| ID
	;

Op:	'+'
	| '-'
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



