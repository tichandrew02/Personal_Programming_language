
tips_lex: lex.yy.o driver.o
	g++ -g -o tips_lex lex.yy.o driver.o

driver.o: driver.cpp lexer.h
	g++ -g -o driver.o -c driver.cpp

lex.yy.o: lex.yy.c lexer.h
	gcc -g -o lex.yy.o -c lex.yy.c

lex.yy.c: rules.l lexer.h
	flex -o lex.yy.c rules.l

clean: 
	$(RM) *.o lex.yy.c tips_lex

