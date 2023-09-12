#
#	File:	makefile
#	Author:	Matteo Loporchio
#

CXX=g++
CXX_FLAGS=-O3 --std=c++11 -I /Users/matteo/igraph/include/igraph
LD_FLAGS=-L /Users/matteo/igraph/lib -ligraph #-fopenmp

.PHONY: clean

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $^ 

analyzer_full: analyzer_full.o
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LD_FLAGS)

analyzer_gcc: analyzer_gcc.o
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LD_FLAGS)

builder: builder.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

pl_fit: pl_fit.o
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LD_FLAGS)

all: analyzer_full analyzer_gcc builder pl_fit

clean:
	rm -f *.o analyzer_full analyzer_gcc builder pl_fit