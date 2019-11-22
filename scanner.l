%{
#define YYSTYPE struct ASTNode *
#include "ast.h"
#include "parser.tab.h"
extern int yylex();
int lineno = 0;
%}

%% 
"int" 			{printf("encountered int \n");return TYPE;}
"char" 			{return TYPE;}
"uint" 			{printf("encountered uint \n"); return TYPE;}
"bool" 			{return TYPE;}
"string" 		{return TYPE;}
"array" 		{return TYPE;}

";" 			{return SEMICOLON;}
"="				{return EQUAL_TO;}
\n				{ ++lineno; }
[ \t] 			{ /* eat white spaces */  }

"and"			{ printf("encountered and \n"); return OP;}
"or"			{ printf("encountered or \n"); return OP;}
"not"			{ printf("encountered not \n"); return UNARY_OP;}
"+"             { printf("alok"); return PLUS;}
[*/-]			{ return OP; }
"for"			{ printf("encountered for \n"); return FOR; }
"while"			{ printf("encountered while \n"); return WHILE; }
"cout"			{ printf("encountered cout \n"); return OUTPUT; }
"cin"			{ printf("encountered cin \n"); return INPUT; }
"break"			{ printf("encountered break \n"); return BREAK; }
"if"			{ printf("encountered if \n"); return IF; }
"else"			{ printf("encountered else \n"); return ELSE; }
":"			    { return FOR_SEPARATE;}
","				{ return COMMA;}
"["				{ return LEFT_BRACKET; }
"]"				{ return RIGHT_BRACKET; }	
"{"				{ return '{'; }
"}"				{ return '}'; }	
"in"			{ return IN; }
"=="		 	{ return COMPARATOR; }
"<="		 	{ return COMPARATOR; }
">="		 	{ return COMPARATOR; }
"<"		 		{ return COMPARATOR; }
">"		 		{ return COMPARATOR; }

[a-zA-Z][a-zA-Z0-9]* 	{ return ID; }
[0-9][0-9]*				{ yylval = getASTNodeIntLiteral(atoi(yytext));return NUMBER; }

[$]				{ printf("%c\n",yytext[0]); return DOLLAR; }

.				{ printf("Line No %d: Unrecognized character '%c'\n", lineno + 1, yytext[0]);}

