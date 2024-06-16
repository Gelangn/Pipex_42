# Colours
DEFAULT 	= \033[0m
GREEN 		= \033[38;5;46m
WHITE 		= \033[38;5;15m
GREY 		= \033[38;5;8m
ORANGE 		= \033[38;5;202m
RED 		= \033[38;5;160m

# Nombre del proyecto (ejecutable)
NAME = pipex

# Compilador y banderas
CC = gcc
#OS := $(shell uname)

CFLAGS = -Wall -Wextra -Werror -g

# Seudonimos carpetas, ejemplo uso: $S main.c
S = src/

# Otros seudonimos
LIB = lib/libft

# Lista de archivos fuente
SRC = *.c
OBJ = $S$(SRC:.c = .o)

# Dependencias
DEPS = $(LIB)/libft.a

# Reglas

# Regla por defecto
all: $(NAME)
	@echo "$(ORANGE)*** Compilation completed OK ***$(DEFAULT)"
	@echo

# Regla de compilación
%.o: %.c 
	@$(CC) $(CFLAGS) -o $@ -c $<

# Regla para construir el archivo estático
$(NAME): $(OBJ)
	@echo "$(GREEN)*** Compiling libft (call) ***"
	@sleep .5
	@clear
	@make -C $(LIB) all
	@make -C $(LIB) bonus
	@echo "$(GREEN)*** Creating executable ***$(DEFAULT)"
	@$(CC) $(OBJ) $(CFLAGS) -L$(LIB) -lft -o $(NAME)
	@sleep .5
	@clear

# Regla para limpiar archivos objeto
clean:
	@echo "$(RED)[INFO]$(GREY) Deleting!!!$(DEFAULT)"
	@make -C $(LIB) clean
	@sleep .5
	@clear

# Regla para limpiar archivos objeto y el archivo estático
fclean: clean
	@make -C $(LIB) fclean
	@rm -f $(NAME)
	@echo "$(RED)[INFO]$(GREY) Objects removed!!!$(DEFAULT)"
	@sleep .5
	@clear

# Regla para recompilar
re: fclean all

.PHONY: all clean fclean re
