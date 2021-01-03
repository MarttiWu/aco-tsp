CXXFLAGS += -std=c++17 -Wall -O3

CPPFLAGS += 

SOURCES := $(shell find . -name '*.cpp')

HEADERS := $(shell find . -name '*.h')

OUTPUT := main

all: dep

dep: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(OUTPUT) $(SOURCES) -I./lib/

clean:
	$(RM) $(OUTPUT)

