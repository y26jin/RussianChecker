CC = g++
CPPFLAGS = -fPIC -std=c++14
LDFLAGS = -shared

SOURCES = checker.cpp
HEADERS = checker.h
OBJECTS = checker.so


all: checker.o example.o unittests.o

clean:
	rm -rf libchecker.so
	rm -rf example
	rm -rf unittests

checker.o : 
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c checker.cpp -o libchecker.so

example.o : example.cpp
	$(CC) -L. -o example example.cpp -lchecker

unittests.o : unittests.cpp
	$(CC) -L. -o unittests unittests.cpp -lchecker
