SOURCES := $(shell find . -name "*.cpp")
OBJS = $(SOURCES:.cpp=.o)
OUT = launcher

all:
	@g++ -std=c++11 -Wall -o $(OUT) $(SOURCES) -lsfml-graphics -lsfml-window -lsfml-system
	@./launcher

# clean house
clean:
	rm -f $(OBJS) $(OUT)
