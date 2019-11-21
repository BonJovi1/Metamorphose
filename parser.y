%{
#include <stdio.h>
#include "ast.h"
#define YYSTYPE struct ASTNode *
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
%token COMPARATOR
%token WHILE
%token IN
%token INPUT
%token OUTPUT
%%

Goal:	Exprs DOLLAR {printf("Rule accepted"); return 0;}
	 | DOLLAR {printf("Rule accepted"); return 0;}

Exprs: Expr '\n' Exprs { printPostFix($1); printf("\n>>"); }
	 | Expr '\t' Exprs
	 | Expr Exprs
     | Expr
     ;

Expr: assignment
	| declaration
	| for_statement
	| while_statement
	| print_statement
	| scan_statement
	;

declaration: TYPE ID SEMICOLON 
		 ;

assignment: ID EQUAL_TO operation SEMICOLON 
		 ;

operation: operation OP Term { $$ = getASTNodeBinaryOp($1, $1, $2); printPostFix($$);}
		 | Term 
		 | UNARY_OP Term 
		 ;

prints_possibilities: prints prints_possibilities
					| prints
					
prints: NUMBER
	  | ID
	  | Exprs

print_statement: OUTPUT '{' prints_possibilities '}' SEMICOLON
scan_statement: INPUT '{' ID '}' SEMICOLON

condition: operation COMPARATOR operation 

for_statement: FOR variable IN LEFT_BRACKET Term FOR_SEPARATE Term FOR_SEPARATE Term RIGHT_BRACKET '{' Exprs '}'

while_statement: WHILE LEFT_BRACKET condition RIGHT_BRACKET '{' Exprs '}'

Term: NUMBER { $$ = getASTNodeIntLiteral(yylval); }
	| ID
	;

variable: ID

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



