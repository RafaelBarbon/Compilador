CC := gcc
SRC := src
OBJ := bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: bin compilador

compilador: $(OBJECTS)
	$(CC) $^ -o $@

bin:
	mkdir -p bin

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) -c $< -o $@