ac:	flex.l bison.y 
	bison -d bison.y
	flex flex.l
	g++ -Wall -o $@ bison.tab.c lex.yy.c -ll
clean:
	rm ac *.yy.c bison.tab.c bison.tab.h 2>/dev/null
