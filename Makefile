parser: scanner.l parser.y
	bison -d parser.y
	flex scanner.l
	gcc -o parser lex.yy.c parser.tab.c ast.c -ll

clean:
	rm lex.yy.c parser.tab.c parser.tab.h parser

# 