#CXXFLAGS+=-Wc++11-extensions
#CXX=g++

CXX=clang++
CXXFLAGS=-std=c++11 -Wall -pedantic -lpthread

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

BIN := $(current_dir).out ver3.out ver2.out

dirs:
	@echo 'make file path = $(mkfile_path)'
	@echo 'current dir = $(current_dir)'
	@echo 'MAKEFILE LIST = $(MAKEFILE_LIST)'
	@echo 'cur dir = $(CURDIR)'

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: ver3.out


ver3.out : ver3.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

ver2.out : ver2.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm -f $(BIN)

