CC = gcc
CFLAGS = -I./include -Wall --pedantic
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Lista de arquivos de origem, excluindo ls.c
SRCS = $(filter-out $(SRC_DIR)/ls.c, $(wildcard $(SRC_DIR)/*.c))

# Gera os nomes dos arquivos objetos
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nome do executável principal
TARGET = $(BIN_DIR)/shell

# Nome do binário para ls.c
LS_TARGET = $(BIN_DIR)/ls

all: $(TARGET) $(LS_TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^ -lreadline

$(LS_TARGET): $(OBJ_DIR)/ls.o
	mkdir -p $(BIN_DIR)
	$(CC) -o $@ $< -lreadline

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(LS_TARGET)

.PHONY: all clean
