CC=g++
CFLAGS=-c -Wall -ansi -pedantic
DEPS=-lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework
CPP= -std=c++0x
SOURCES=nbody.cpp main.cpp
ALTSOURCES=unit_test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
ALTOBJECTS=$(ALTSOURCES:.cpp=.o)
EXECUTABLE=NBody
ALTEXECUTABLE=NTest

.PHONY: all main test

all: main test

main: $(EXECUTABLE)

test: $(ALTEXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CPP) $(OBJECTS) $(DEPS) -o $@

$(ALTEXECUTABLE): $(ALTOBJECTS)
	$(CC) $(CPP) $(ALTOBJECTS) $(DEPS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm *.o $(OBJECTS) $(ALTOBJECTS) NBody NTest
