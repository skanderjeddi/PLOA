CC = g++ -Wall -std=c++11
CCO = $(CC) -c $<
OBJECTS = tuile.o main.o
all : $(OBJECTS)
	$(CC) -o projet $(OBJECTS)
	./projet
tuile.o : tuile.cpp tuile.hpp
	$(CCO)
main.o : main.cpp
	$(CCO)
clean :
	rm -f *.o tp
