# Nombre del ejecutable
TARGET = snake

# Directorios de código fuente y objeto
SRC_DIR = src
OBJ_DIR = obj

# Lista de archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generar nombres de archivos objeto a partir de los archivos fuente
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Compilador y opciones de compilación
CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

# Bibliotecas a enlazar
LDFLAGS = -lSDL2

# Regla por defecto: compilar todo
all: $(TARGET)

# Regla para el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Regla para los archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para crear el directorio de objetos
$(OBJ_DIR):
	mkdir -p $@

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Fuerza la reconstrucción de todo
rebuild: clean all

# Indica que "clean" y "rebuild" no son archivos
.PHONY: clean rebuild
