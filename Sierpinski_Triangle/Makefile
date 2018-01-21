CC=g++
CFLAGS=-c -Wall -ansi -pedantic
DEPS=-lsfml-graphics -lsfml-window -lsfml-system
CPP= -std=c++11
SOURCES=sierpinski_main.cpp sierpinski.cpp
ALTSOURCES=original_main.cpp original.cpp
OBJECTS=$(SOURCES:.cpp=.o)
ALTOBJECTS=$(ALTSOURCES:.cpp=.o)
EXECUTABLE=sierpinski
ALTEXECUTABLE=original

.PHONY: all main alt

all: main alt

main: $(EXECUTABLE)

alt: $(ALTEXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CPP) $(OBJECTS) $(DEPS) -o $@

$(ALTEXECUTABLE): $(ALTOBJECTS)
	$(CC) $(CPP) $(ALTOBJECTS) $(DEPS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm *.o $(OBJECTS) $(ALTOBJECTS) sierpinski original
