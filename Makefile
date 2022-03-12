CXX=g++
CFLAGS=-O2
EXE=cross_verify
SRC=$(wildcard *.cpp)

all: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CFLAGS) $^ -o $@

test: $(EXE)
	./$(EXE) | python3 ./verify.py

clean:
	-rm  *~ *.o

clobber: clean
	-rm $(EXE)
