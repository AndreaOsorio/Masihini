grammar: lex.yy.c y.tab.c
	g++ -std=gnu++11 -c grammar.tab.c lex.yy.c
	ar rvs .lexgram.a grammar.tab.o lex.yy.o
	g++ -std=gnu++11 -Wall -Wextra Semantics/Type.hpp Semantics/VarNode.hpp Semantics/VarTable.hpp Semantics/FuncNode.hpp Semantics/FuncDir.hpp Memory/MemoryDispatcher.hpp Memory/MemoryFrame.hpp main.cpp .lexgram.a


lex.yy.c:
		flex ./Grammar/lex.l

y.tab.c:
	bison -d ./Grammar/grammar.y





clean:
	rm -f lex.yy.c a.out grammar.tab.o grammar.tab.h lex.yy.o lexgram.a grammar.output grammar.tab.c 
	rm -f ./Memory/MemoryDispatcher.hpp.gch ./Memory/MemoryFrame.hpp.gch
	rm -f ./Semantics/FuncDir.hpp.gch  ./Semantics/FuncNode.hpp.gch  ./Semantics/SemanticRuleSet.hpp.gch
	rm -f ./Semantics/Type.hpp.gch ./Semantics/VarNode.hpp.gch ./Semantics/VarTable.hpp.gch 

check:
	bison -v grammar.y


test:
	./a.out < ./TestFiles/enter.code
