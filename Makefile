FLAGS = -Werror -std=c++17 -Wall
CC= c++ $(FLAGS)

TST=src/intel8080/i8080_tests
SRC=src
INCLUDE=$(SRC)/intel8080
OBJS=$(SRC)/intel8080/objs

all: clean install run

install: 
	@ mkdir -p $(OBJS)
	@ $(CC) -c $(INCLUDE)/i8080.cpp -I $(INCLUDE)/ -o $(OBJS)/i8080.o
	@ $(CC) -g $(TST)/i8080_tests.cpp $(OBJS)/i8080.o -I $(INCLUDE)/ -o $(TST)/bin/i8080_tests 
	@ echo "*** compiled "
clean:
	@ rm -fr $(OBJS)
	@ rm -fr $(BIN)/main

run:
	@ $(TST)/bin/i8080_tests
