# chess engine makefile
CC=g++
#CC=g++ -fprofile-arcs -ftest-coverage

Hal9000: position.o evaluate.o main.o
	$(CC) position.o evaluate.o main.o -g -o Hal9000

position.o: position.h position.cpp
	$(CC) -c -g position.cpp

evaluate.o: evaluate.h evaluate.cpp
	$(CC) -c -g evaluate.cpp

main.o: position.h main.cpp
	$(CC) -c -g main.cpp

clean:
	rm *.o *.gcov *.gcda *.gcno Hal9000
