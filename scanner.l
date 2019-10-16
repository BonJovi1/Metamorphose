%{
#include "parser.tab.h"
int lineno = 0;
%}

%% 
"int" 			{printf("encountered"); return TYPE;}
"char" 			{printf("encountered"); return TYPE;}
"uint" 			{printf("encountered"); return TYPE;}
"bool" 			{printf("encountered"); return TYPE;}
"string" 		{printf("encountered"); return TYPE;}
"array" 		{printf("encountered"); return TYPE;}

";" 			{return SEMICOLON;}
"="				{return EQUAL_TO;}
[ \t] 			{ /* eat white spaces */  }

[a-zA-Z][a-zA-Z0-9]* 	{ printf("Scanned \n"); return ID; }

[0-9][0-9]*		{ return NUMBER; }
[+-]			{ return yytext[0]; }
[$]				{printf("%c\n",yytext[0]); return yytext[0]; }
\n				{ ++lineno; return '\n'; }
.				{ printf("Line No %d: Unrecognized character '%c'\n", lineno + 1, yytext[0]);}

