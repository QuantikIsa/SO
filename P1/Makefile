PROGRAM = a.out

# Usar el compilador gcc con las cflags
CC = gcc
CFLAGS = -Wall -Wextra -g
VALGRINDFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes

# Archivos fuente y objetos
SRC = p1.c hist_cmd.c help.c cmd.c files.c
OBJ = $(SRC:.c=.o)

# Con "make" all es la ejecución por defecto (lo compila y luego ejecuta)
all: $(PROGRAM)

$(PROGRAM): $(OBJ)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $@ $(OBJ)


run: $(PROGRAM)
	@if command -v rlwrap >/dev/null 2>&1; then \
		rlwrap ./$(PROGRAM) -p; \
	else \
		echo "rlwrap no está instalado, ejecutando sin rlwrap..."; \
		./$(PROGRAM) -p; \
	fi