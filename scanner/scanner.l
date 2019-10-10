%{
int lineno = 0;
%}

%% 
[a-zA-Z0-9+-]	{ printf("Scanning %c \n",  yytext[0]); }
\n		{ ++lineno; }
.		{ printf("Line No %d: Unrecognized character '%c'\n", lineno + 1, yytext[0]);}

