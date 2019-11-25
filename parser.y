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
%token WHILE
%token IN
%token INPUT
%token OUTPUT
%token COMMA
%token BREAK
%token FUNC
%%

/* Now, we define the Context Free Grammar of our language
After every substitution rule, the stuff inside the brackets: { } is C code.  
Any code written in this language must end with a '$' symbol. 
*/

Goal:  Exprs DOLLAR { printf("Rule accepted \n"); printPostFix($1); return 0;}
	 | DOLLAR {printf("Rule accepted"); return 0;}

Exprs: Expr Exprs { $$ = getASTNodeExpression($1, $2);}
     | Expr { $$ = $1; }
     ;

/* An Expression would comprise of multiple statements. 
The statements can be of various types, as given in the CFG rule below.
*/

Expr: assignment {$$ = $1;}
	| declaration {$$ = $1;}
	| control_flow_statement
	| io_statement
	;

control_flow_statement: for_statement
					  | while_statement
					  | if_statement

io_statement: print_statement
			| scan_statement

/* Defining declaration statements
eg. int a;
and there is provision for multiple declarations too! eg. int a,b = 5; 
*/

declaration: INT_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(INTS, $2);}
		   | CHAR_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(CHARS, $2); }
		   | UINT_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(UINTS, $2); }
		   | BOOL_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(BOOLS, $2); }
		   | STRING_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(STRINGS, $2); }
		   | ARRAY_TYPE variable SEMICOLON { $$ = getASTNodeDeclaration(ARRAYS, $2); }
		   ;

// multiple_ids: variable COMMA multiple_ids 
// 			| variable {$$ = $1;}
// 			;

/* Defining assignment statements
eg. a = 5;
*/

assignment: variable EQUAL_TO operation SEMICOLON { $$ = getASTNodeAssignment($1, $3); }
		  ;

operation: operation AND_OP Term { $$ = getASTNodeBinaryOp($1, $3, AND);}
		 | operation OR_OP Term  { $$ = getASTNodeBinaryOp($1, $3, OR);}
		 | operation ADD_OP Term { $$ = getASTNodeBinaryOp($1, $3, ADD);}
		 | operation SUB_OP Term { $$ = getASTNodeBinaryOp($1, $3, SUB);}
		 | operation MUL_OP Term { $$ = getASTNodeBinaryOp($1, $3, MUL);}
		 | operation DIV_OP Term { $$ = getASTNodeBinaryOp($1, $3, DIV);}
		 | Term 				 { $$ = $1; }
		 | UNARY_OP Term 
		 ;

/* Defining IO statements
eg. cout{a}; cin{n, k};
*/

print_statement: OUTPUT '{' prints_possibilities '}' SEMICOLON
scan_statement:  INPUT '{' variable '}' SEMICOLON

prints_possibilities: prints prints_possibilities
					| prints
					
prints: variable
	  | Exprs

/* Defining Control Flow statements
eg. if[a<5] { } else { }
	while[a<5]
	for var in [1:3:1] { } 
*/

condition: operation EQ_COMP operation { $$ = getASTNodeCondition($1, $3, EQ);}
		 | operation LE_COMP operation { $$ = getASTNodeCondition($1, $3, LE);}
		 | operation GE_COMP operation { $$ = getASTNodeCondition($1, $3, GE);}
		 | operation LT_COMP operation { $$ = getASTNodeCondition($1, $3, LT);}
		 | operation GT_COMP operation { $$ = getASTNodeCondition($1, $3, GT);}

for_statement: FOR variable IN for_loop '{' Exprs '}' 
for_loop: LEFT_BRACKET Term FOR_SEPARATE Term FOR_SEPARATE Term RIGHT_BRACKET {$$=getASTNodeForLoop($2, $4, $6);}
			   

while_statement: WHILE LEFT_BRACKET condition RIGHT_BRACKET '{' Exprs '}' 

if_statement: IF LEFT_BRACKET condition RIGHT_BRACKET '{' Exprs '}' 
			| IF LEFT_BRACKET condition RIGHT_BRACKET '{' Exprs '}' ELSE '{' Exprs '}'

Term: NUMBER { $$ = yylval; }
	| variable { $$ = $1; }
	;

variable: ID {$$ = yylval;}
%%

yyerror(char *s)
{
        fprintf(stderr, "error: %s\n", s);
}


int main(int argc, char **argv)
{
        yyparse();
        printf("Parsing Over\n");
        return 0;
}



