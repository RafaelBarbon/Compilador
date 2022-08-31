CC := gcc
SRC := src
OBJ := bin
#MAKEBIN := mkdir -p bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

compilador: $(OBJECTS)
	$(CC) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) -c $< -o $@