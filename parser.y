%{
#include <stdio.h>
#include "ast.h"
#define YYSTYPE struct ASTNode *

extern int yylex();
extern int yyparse();
extern FILE *yyin;
%}

%token NUMBER ID
%token IF ELSE 
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
%token COMMA
%token BREAK
%token PLUS
%%

Goal:	Exprs DOLLAR {printf("Rule accepted \n"); return 0;}
	 | DOLLAR {printf("Rule accepted"); return 0;}

Exprs: Expr Exprs
     | Expr
     ;

Expr: assignment
	| declaration
	| for_statement
	| while_statement
	| print_statement
	| scan_statement
	| if_statement
	;

declaration: TYPE multiple_ids SEMICOLON 
		 ;
multiple_ids: ID COMMA multiple_ids
			| ID

assignment: ID EQUAL_TO operation SEMICOLON {printPostFix($3);}
		 ;

operation: operation OP Term 
		 | operation PLUS Term { $$ = getASTNodeBinaryOp($1, $3, ADD);}
		 | Term { $$ = $1;}
		 | UNARY_OP Term 
		 ;

prints_possibilities: prints prints_possibilities
					| prints
					
prints: NUMBER
	  | ID
	  | Exprs

print_statement: OUTPUT '{' prints_possibilities '}' SEMICOLON
scan_statement: INPUT '{' multiple_ids '}' SEMICOLON

condition: operation COMPARATOR operation 

for_statement: FOR variable IN LEFT_BRACKET Term FOR_SEPARATE Term FOR_SEPARATE Term RIGHT_BRACKET 
				'{' Exprs '}'

while_statement: WHILE LEFT_BRACKET condition RIGHT_BRACKET '{' Exprs '}'

if_statement: IF LEFT_BRACKET condition RIGHT_BRACKET '{' Exprs '}'
			| IF LEFT_BRACKET condition RIGHT_BRACKET '{' Exprs '}' ELSE '{' Exprs '}'

Term: NUMBER { $$ = yylval; }
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



