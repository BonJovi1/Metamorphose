parser: scanner.l parser.y
	flex scanner.l
	bison -d parser.y
	gcc -o parser lex.yy.c parser.tab.c -ll

clean:
	rm lex.yy.c parser.tab.c parser.tab.h
