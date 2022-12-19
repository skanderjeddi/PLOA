CXX = g++
CXXFLAGS = -std=c++11 -Wall

SOURCES := $(shell find . -name "*.cpp")
OBJS = $(SOURCES:.cpp=.o)
OUT = launcher

.PHONY: all clean

all: $(OUT)
	./launcher

# clean house
clean:
	rm -f $(OBJS) $(OUT)

$(OUT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SOURCES) -lsfml-graphics -lsfml-window -lsfml-system

