CC = g++ -Wall -std=c++11
CCO = $(CC) -c $<
OBJECTS = tile.o board.o main.o
all : $(OBJECTS)
	$(CC) -o dominos $(OBJECTS)
	./dominos
tile.o : tile.cpp tile.hpp
	$(CCO)
board.o : board.cpp board.hpp
	$(CCO)
main.o : main.cpp
	$(CCO)
clean :
	rm -f *.o tp
