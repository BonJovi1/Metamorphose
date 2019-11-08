%{
#include "parser.tab.h"
int lineno = 0;
%}

%% 
"int" 			{printf("encountered\n"); return TYPE;}
"char" 			{printf("encountered\n"); return TYPE;}
"uint" 			{printf("encountered\n"); return TYPE;}
"bool" 			{printf("encountered\n"); return TYPE;}
"string" 		{printf("encountered\n"); return TYPE;}
"array" 		{printf("encountered\n"); return TYPE;}

";" 			{return SEMICOLON;}
"="				{return EQUAL_TO;}
[ \t] 			{ /* eat white spaces */  }

"and"			{printf("encountered\n"); return OP;}
"or"			{printf("encountered\n"); return OP;}
"not"			{printf("encountered\n"); return UNARY_OP;}
[+*/-]			{ return OP; }
"for"			{ printf("encountered\n"); return FOR; }
":"			    { return FOR_SEPARATE;}
"["				{ return LEFT_BRACKET; }
"]"				{ return RIGHT_BRACKET; }				

[a-zA-Z][a-zA-Z0-9]* 	{ printf("Scanned \n"); return ID; }
[0-9][0-9]*				{ printf("Scanned \n"); return NUMBER; }

[$]				{ printf("%c\n",yytext[0]); return DOLLAR; }
\n				{ ++lineno; return '\n'; }
.				{ printf("Line No %d: Unrecognized character '%c'\n", lineno + 1, yytext[0]);}

