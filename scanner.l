%{
#include "parser.tab.h"
int lineno = 0;
%}

%% 
"int" 			{return TYPE;}
"char" 			{return TYPE;}
"uint" 			{printf("encountered int \n"); return TYPE;}
"bool" 			{return TYPE;}
"string" 		{return TYPE;}
"array" 		{return TYPE;}

";" 			{return SEMICOLON;}
"="				{return EQUAL_TO;}
[ \t] 			{ /* eat white spaces */  }

"and"			{ return OP;}
"or"			{ return OP;}
"not"			{ return UNARY_OP;}
[+*/-]			{ return OP; }
"for"			{ return FOR; }
"while"			{ return WHILE; }
"cout"			{ return OUTPUT; }
"cin"			{ return INPUT; }
":"			    { return FOR_SEPARATE;}
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
[0-9][0-9]*				{ return NUMBER; }

[$]				{ printf("%c\n",yytext[0]); return DOLLAR; }
\n				{ ++lineno; return '\n'; }
.				{ printf("Line No %d: Unrecognized character '%c'\n", lineno + 1, yytext[0]);}

