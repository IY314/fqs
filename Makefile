mkbindir:
	mkdir -p bin

build: mkbindir
	$(CXX) src/*.cc -o bin/fqs -std=c++17 -Wall -Werror -Wextra
