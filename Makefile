parser: scanner.l parser.y ast.c
	bison -d parser.y
	flex scanner.l
	gcc -w -o parser lex.yy.c parser.tab.c ast.c -ll

clean:
	rm lex.yy.c parser.tab.c parser.tab.h parser

# 