SOURCES := $(shell find . -name "*.cpp")
OBJS = $(SOURCES:.cpp=.o)
OUT = loapro

all:
	g++ -std=c++11 -Wall -o $(OUT) $(SOURCES)
	./loapro $(game)

# clean house
clean:
	rm -f $(OBJS) $(OUT)
