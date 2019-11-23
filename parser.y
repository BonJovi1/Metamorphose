%{
#include <stdio.h>
#include "ast.h"
#define YYSTYPE struct ASTNode *

extern int yylex();
extern int yyparse();
extern FILE *yyin;
%}

%{
// Defining Tokens, which the parser obtains from the scanner
// These block of statements have C code inside of them! 
%}

%token NUMBER ID
%token IF ELSE 

%token INT_TYPE
%token CHAR_TYPE
%token BOOL_TYPE
%token UINT_TYPE
%token STRING_TYPE
%token ARRAY_TYPE 2DARRAY_TYPE

%token SEMICOLON
%token EQUAL_TO
%token DOLLAR

%token UNARY_OP
%token AND_OP
%token OR_OP
%token ADD_OP
%token SUB_OP
%token MUL_OP
%token DIV_OP

%token EQ_COMP
%token LE_COMP
%token GE_COMP
%token LT_COMP
%token GT_COMP

%token FOR LEFT_BRACKET RIGHT_BRACKET 
%token FOR_SEPARATE
%token COMPARATOR
%token WHILE
%token IN
%token INPUT
%token OUTPUT
%token COMMA
%token BREAK
%%

/* Now, we define the Context Free Grammar of our language
After every substitution rule, the stuff inside the brackets: { } is C code.  
Any code written in this language must end with a '$' symbol. 
*/

Goal:  Exprs DOLLAR {printf("Rule accepted \n"); return 0;}
	 | DOLLAR {printf("Rule accepted"); return 0;}

Exprs: Expr Exprs
     | Expr
     ;

/* An Expression would comprise of multiple statements. 
The statements can be of various types, as given in the CFG rule below.
*/

Expr: assignment
	| declaration
	| control_flow_statement
	| io_statement
	;

control_flow_statement: for_statement
					  | while_statement
					  | if_statement

io_statement: print_statement
			| scan_statement

/* Defining declaration statements
eg. int a = 5;
and there is provision for multiple declarations too! eg. int a,b = 5; 
*/

declaration: INT_TYPE multiple_ids SEMICOLON 
		   | CHAR_TYPE multiple_ids SEMICOLON 
		   | UINT_TYPE multiple_ids SEMICOLON 
		   | BOOL_TYPE multiple_ids SEMICOLON 
		   | STRING_TYPE multiple_ids SEMICOLON 
		   | ARRAY_TYPE multiple_ids SEMICOLON 

multiple_ids: ID COMMA multiple_ids
			| ID

/* Defining assignment statements
eg. a = 5;
*/

assignment: ID EQUAL_TO operation SEMICOLON {printPostFix($3);}
		  ;

operation: operation AND_OP Term
		 | operation OR_OP Term
		 | operation ADD_OP Term { $$ = getASTNodeBinaryOp($1, $3, ADD);}
		 | operation SUB_OP Term
		 | operation MUL_OP Term
		 | operation DIV_OP Term
		 | Term 				 { $$ = $1;}
		 | UNARY_OP Term 
		 ;

/* Defining IO statements
eg. cout{a}; cin{n, k};
*/

print_statement: OUTPUT '{' prints_possibilities '}' SEMICOLON
scan_statement:  INPUT '{' multiple_ids '}' SEMICOLON

prints_possibilities: prints prints_possibilities
					| prints
					
prints: multiple_ids
	  | Exprs

/* Defining Control Flow statements
eg. if[a<5] { } else { }
	while[a<5]
	for var in [1:3:1] { } 
*/

condition: operation COMPARATOR operation 

for_statement: FOR variable IN for_loop '{' Exprs '}'
for_loop: LEFT_BRACKET Term FOR_SEPARATE Term FOR_SEPARATE Term RIGHT_BRACKET 
			   

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



