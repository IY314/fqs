CXX := /usr/bin/c++
WFLAGS := -Wall -Werror -Wextra
IFLAGS := -Iinclude -Ilib/argparse/include
CXXFLAGS := -c -std=c++17 ${WFLAGS} ${IFLAGS}

.PHONY: mkbin all clean

all: mkbin main.o pos.o token.o lex.o util.o errors.o link

mkbin:
	mkdir -p bin

link: mkbin
	${CXX} bin/*.o -o bin/fqs ${WFLAGS}

clean:
	rm -rf bin

main.o: mkbin src/main.cc
	${CXX} src/main.cc -o bin/main.o ${CXXFLAGS}

pos.o: mkbin src/pos.cc
	${CXX} src/pos.cc -o bin/pos.o ${CXXFLAGS}

token.o: mkbin src/token.cc
	${CXX} src/token.cc -o bin/token.o ${CXXFLAGS}

lex.o: mkbin src/lex.cc
	${CXX} src/lex.cc -o bin/lex.o ${CXXFLAGS}

util.o: mkbin src/util.cc
	${CXX} src/util.cc -o bin/util.o ${CXXFLAGS}

errors.o: mkbin src/errors.cc
	${CXX} src/errors.cc -o bin/errors.o ${CXXFLAGS}
