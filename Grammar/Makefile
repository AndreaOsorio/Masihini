all:
	$(MAKE) grammar
	$(MAKE)	lex
	gcc -c grammar.tab.c lex.yy.c
	ar rvs lexgram.a grammar.tab.o lex.yy.o
	g++ -std=c++11 -Wall -Wextra main.cpp lexgram.a


grammar:
	bison -d grammar.y

lex:
	flex lex.l

clean:
		rm -f lex.yy.c grammar.tab.o grammar.tab.h lex.yy.o lexgram.a a.out grammar.output grammar.tab.c

check:
	bison -v grammar.y
