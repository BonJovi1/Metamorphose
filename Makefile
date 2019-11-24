parser: scanner.l parser.y ast.c
	bison -d parser.y
	flex scanner.l
	gcc -Wall -o parser lex.yy.c parser.tab.c ast.c -ll

clean:
	rm lex.yy.c parser.tab.c parser.tab.h parser
