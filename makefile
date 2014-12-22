LEX = flex
YACC = yacc -d -v
CC = gcc -Wall -g
LIBS = -lfl -ly
vpath main bin
vpath %.h  include
vpath %.o  obj
vpath %.c  src
vpath %.l  src
vpath %.y  src
BIN     = ./bin/
INCLUDE = ./include/
OBJ     = ./obj/
SRC     = ./src/


main : ast.o mips.o quad.o symbolTable.o tree.o y.tab.o lex.yy.o 
	$(CC) -o main $(OBJ)ast.o $(OBJ)mips.o $(OBJ)quad.o $(OBJ)symbolTable.o $(OBJ)tree.o $(OBJ)y.tab.o $(OBJ)lex.yy.o $(LIBS)
	mv $@ $(BIN)
	
	
ast.o : $(SRC)ast.c
	$(CC) -c $<
	mv $@ $(OBJ)
mips.o : mips.c
	$(CC) -c $<
	mv $@ $(OBJ)
quad.o : quad.c
	$(CC) -c $<
	mv $@ $(OBJ)
symbolTable.o : symbolTable.c
	$(CC) -c $<
	mv $@ $(OBJ)
tree.o : tree.c
	$(CC) -c $<
	mv $@ $(OBJ)
y.tab.o : y.tab.c
	$(CC) -c $<
	mv $@ $(OBJ)
lex.yy.o : lex.yy.c
	$(CC) -c $<
	mv $@ $(OBJ)
y.tab.c y.tab.h : analyzer.y 
	$(YACC) $<
	mv y.output $(OBJ)
lex.yy.c : lexeur.l
	$(LEX) $<
	
	
archive :
	zip -r VEZIN_Aurelien_MULLER_Isabelle.zip *
	
clean :
	mv lex.yy.c $(BIN)
	mv y.tab.c $(BIN)
	mv y.tab.h $(BIN)
	rm -f $(BIN)* $(OBJ)*
	rm -fr Documentation.bak
	rm *.s
	rm -f $(INCLUDE)y.tab.h
	rm -f $(SRC)y.tab.c
	
doc :
	mkdir -p Documentation
	doxygen -g Documentation $(HEADERS)* $(SOURCES)*
	doxygen Documentation
	mv Documentation ./Documentation.bak/
	mv html ./Documentation.bak/
	mv latex ./Documentation.bak/
	
gdb :
	gdb -q $(BIN)main
	
geany :
	geany $(INCLUDE)* $(SRC)* &
	
mips :
	spim -notrap -file *.s
	
run :
	$(BIN)./main test.c
	
valgrind :
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes -v $(BIN)main
