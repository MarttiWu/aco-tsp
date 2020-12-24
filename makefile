CXXFLAGS += -std=c++17 -Wall 

CPPFLAGS += 

SOURCES := $(shell find . -name '*.cpp')

HEADERS := $(shell find . -name '*.h')

OUTPUT := main

all: dep

dep: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(OUTPUT) $(SOURCES) 

clean:
	$(RM) $(OUTPUT)

