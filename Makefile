CFLAGS=-std=c++11
IDIR=./include
SRC=./src
OBJ=graph-utils.o manager.o graph.o

all: graph-utils

graph-utils: graph-utils.o
	g++ $(OBJ) -o graph-utils $(CFLAGS)

graph-utils.o: $(SRC)/graph-utils.cpp manager.o
	g++ -c $(SRC)/graph-utils.cpp $(CFLAGS)

manager.o: $(IDIR)/manager.cpp graph.o
	g++ -c $(IDIR)/manager.cpp $(CFLAGS)

graph.o: $(IDIR)/graph.cpp
	g++ -c $(IDIR)/graph.cpp $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o include/*.o graph-utils