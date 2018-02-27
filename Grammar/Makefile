all:
	$(MAKE) parser
	$(MAKE) scanner
	g++ -std=c++11 -Wall -Wextra parser.tab.c lex.yy.c main.cpp
	./a.exe < sample_input

parser:
	bison -d parser.y

scanner:
	flex scanner.l	
