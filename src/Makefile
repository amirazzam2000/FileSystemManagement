CXX = g++
DIR = ../headers/
CXXFLAGS = -Wall -Werror -Wextra -pedantic -lm -std=c++17 -g -fsanitize=address -I$(DIR) -Wno-write-strings
LDFLAGS =  -fsanitize=address


LBLIBS = FileReader.h FAT.h Ext2.h FileSystem.h DirectoryManager.h

SRC = FileReader.cc FAT.cc Ext2.cc FileSystem.cc DirectoryManager.cc Main.cc
OBJ = $(SRC:.cc=.o)
EXEC = shooter

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $($(DIR)LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)