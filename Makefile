CC = gcc
CFLAGS = -I./include -Wall --pedantic
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Lista de arquivos de origem
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Gera os nomes dos arquivos objetos
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Nome do executável
TARGET = $(BIN_DIR)/PROJETO2

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^ -lreadline

$(OBJS): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
