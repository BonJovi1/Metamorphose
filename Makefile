parser: scanner.l parser.y ast.h ast.c interpreter.cpp Interpreter.h
	bison -d parser.y
	flex scanner.l
	g++ -w -o metamorphose ast.c interpreter.cpp parser.tab.c lex.yy.c -ll

clean:
	rm lex.yy.c parser.tab.c parser.tab.h metamorphose
