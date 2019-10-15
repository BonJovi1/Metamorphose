%{
int lineno = 0;
%}

%% 
[ \t] 		{ /* eat white spaces */  }
[a-zA-Z0-9+-]	{printf("Scanning %c\n",yytext[0]) ; return yytext[0];}
[$]	{printf("%c\n",yytext[0]); return yytext[0]; }
\n		{ ++lineno; return '\n'; }
.		{ printf("Line No %d: Unrecognized character '%c'\n", lineno + 1, yytext[0]);}

