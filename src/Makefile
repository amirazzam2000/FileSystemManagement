CXX = g++
DIR = ../headers/
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address -I$(DIR)
LDFLAGS =  -fsanitize=address


LBLIBS = FileReader.h

SRC = FileReader.cc Main.cc
OBJ = $(SRC:.cc=.o)
EXEC = Main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(DIR)$(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)