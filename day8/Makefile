#CXXFLAGS+=-Wc++11-extensions
#CXX=g++

CXX=clang++
CXXFLAGS=-std=c++11 -Wall -pedantic

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

BIN := $(current_dir).out

dirs:
	@echo 'make file path = $(mkfile_path)'
	@echo 'current dir = $(current_dir)'
	@echo 'MAKEFILE LIST = $(MAKEFILE_LIST)'
	@echo 'cur dir = $(CURDIR)'

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c $<

clean:
	rm -f *.o
	rm $(BIN)

