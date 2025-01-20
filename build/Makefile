# Name der Ziel-Bibliothek
LIBRARY = libslang.so
# Verzeichnisse für Quell- und Header-Dateien
INCLUDE_DIR = ../core/include
SRC_DIR = ../core/src
# Quell-Dateien
SRCS = $(wildcard $(SRC_DIR)/*.c)
# Objekt-Dateien (ersetzt .c durch .o)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)
# Compiler und Flags
CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -I$(INCLUDE_DIR)
LDFLAGS = -shared
# Default-Ziel
all: $(LIBRARY)
# Erstellen der Shared Library
$(LIBRARY): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
# Erstellen der Objekt-Dateien
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
# Clean-Ziel, um generierte Dateien zu entfernen
clean:
	rm -f $(OBJS) $(LIBRARY)
# Phony-Ziele definieren
.PHONY: all clean