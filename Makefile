CXX		  := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=
EXECUTABLE	:= nfa_simulation


all: $(EXECUTABLE) 

run: clean all
	clear
	./$(EXECUTABLE) 

$(EXECUTABLE): ./*.cc
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)

clean:
	-rm nfa_simulation
