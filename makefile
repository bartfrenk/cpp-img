CC=g++
LIBS = -lfreeimage
CFLAGS=-std=c++11 -g -Wall -pg
LFLAGS=-pg -Wall

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# transforms *.cpp source paths into corresponding *.o binary paths
make_objs = $(patsubst %.cpp,%.o,$(subst $(SRC_DIR), $(OBJ_DIR), $(1)))
find_src = $(shell find ${SRC_DIR}/$(1) -name \*.cpp)

SRC = $(shell find $(SRC_DIR) -name \*.cpp)
_OBJECTS = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC))
OBJECTS = $(_OBJECTS:%.cpp=%.o)

.PHONY: clean

$(BIN_DIR)/test.out: $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(LIBS) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $<


clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
