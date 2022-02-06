CXX := /usr/bin/c++
CPP_FLAGS := -c -std=c++17 -Wall -Werror -Wextra -Iinclude

.PHONY: mkbin all clean

all: mkbin main.o pos.o token.o lex.o util.o

mkbin:
	mkdir -p bin

clean:
	rm -rf bin

main.o: mkbin src/main.cc
	${CXX} src/main.cc -o bin/main.o ${CPP_FLAGS}

pos.o: mkbin src/pos.cc
	${CXX} src/pos.cc -o bin/pos.o ${CPP_FLAGS}

token.o: mkbin src/token.cc
	${CXX} src/token.cc -o bin/token.o ${CPP_FLAGS}

lex.o: mkbin src/lex.cc
	${CXX} src/lex.cc -o bin/lex.o ${CPP_FLAGS}

util.o: mkbin src/util.cc
	${CXX} src/util.cc -o bin/util.o ${CPP_FLAGS}
