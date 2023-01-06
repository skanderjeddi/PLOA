CXX = g++
CXXFLAGS = -std=c++11 -g

SOURCES := $(shell find . -name "*.cpp")
OBJS = $(SOURCES:.cpp=.o)
OUT = launcher

.PHONY: all clean

all: $(OUT)
	@./bin/launcher

# clean house
clean:
	rm -f $(OBJS) $(OUT)

$(OUT): $(OBJS)
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) -o ./bin/$(OUT) $(SOURCES) -lsfml-graphics -lsfml-window -lsfml-system
