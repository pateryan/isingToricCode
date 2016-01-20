CC = g++
CFLAGS = -Wall -Werror -O3 -Wno-unused-variable -std=c++11
OBJECTS = test.o site.o lattice.o

SOURCEDIR = src
BUILDDIR = build
APPNAME = test

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)

$(info $$SOURCES is [${SOURCES}])
$(info $$OBJECTS is [${OBJECTS}])

$(APPNAME) : $(OBJECTS)
	g++ -o test $(CFLAGS) $(OBJECTS)

test.o : test.cpp site.h
	g++ -c $(CFLAGS) test.cpp
site.o : site.cpp site.h
	g++ -c $(CFLAGS) site.cpp
lattice.o : lattice.cpp lattice.h
	g++ -c $(CFLAGS) lattice.cpp

clean :
	rm *.o
	rm $(APPNAME)
