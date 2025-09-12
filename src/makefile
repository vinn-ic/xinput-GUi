# Nome do executável final
TARGET = main

# Arquivos fonte
SRC = main.c command.c

# Flags do compilador
CFLAGS = -Wall -g $(shell pkg-config --cflags gtk+-3.0)

# Bibliotecas necessárias (GTK3, X11 e XInput2)
LIBS = $(shell pkg-config --libs gtk+-3.0) -lX11 -lXi

# Compilador
CC = gcc

# Regra padrão
all: $(TARGET)

# Como compilar o programa
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Limpeza
clean:
	rm -f $(TARGET) *.o
