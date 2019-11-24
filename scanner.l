%{
#define YYSTYPE struct ASTNode *
#include "ast.h"
#include "parser.tab.h"
extern int yylex();
int lineno = 0;
%}

%% 
\n				{ ++lineno; }
[ \t] 			;
"int" 			{printf("encountered int \n"); return INT_TYPE;}
"char" 			{return CHAR_TYPE;}
"uint" 			{printf("encountered uint \n"); return UINT_TYPE;}
"bool" 			{return BOOL_TYPE;}
"string" 		{return STRING_TYPE;}
"array[]" 		{return ARRAY_TYPE;}

[;] 			{return ';';}
"="				{return EQUAL_TO;}

"and"			{ return AND_OP;}
"or"			{ return OR_OP;}
"not"			{ return UNARY_OP;}
"+"             { return ADD_OP;}
"-"				{ return SUB_OP;}
"*"				{ return MUL_OP;}
"/"				{ return DIV_OP;}

"for"			{ printf("encountered for \n"); return FOR; }
"while"			{ return WHILE; }
"cout"			{ return OUTPUT; }
"cin"			{ printf("encountered cin \n"); return INPUT; }
"break"			{ return BREAK; }
"if"			{ printf("encountered if \n"); return IF; }
"else"			{ printf("encountered else \n"); return ELSE; }

":"			    { return FOR_SEPARATE;}
","				{ return COMMA;}
"["				{ return LEFT_BRACKET; }
"]"				{ return RIGHT_BRACKET; }	
"{"				{ return '{'; }
"}"				{ return '}'; }	

"in"			{ return IN; }
"=="		 	{ return EQ_COMP; }
"<="		 	{ return LE_COMP; }
">="		 	{ return GE_COMP; }
"<"		 		{ return LT_COMP; }
">"		 		{ return GT_COMP; }

[a-zA-Z][a-zA-Z0-9]* 	{ yylval = getASTNodeID(yytext); return ID;}
[0-9][0-9]*				{ yylval = getASTNodeIntLiteral(atoi(yytext)); return NUMBER; }

[$]				{ printf("%c\n",yytext[0]); return DOLLAR; }

.				{ printf("Line No %d: Unrecognized character '%c'\n", lineno + 1, yytext[0]);}

