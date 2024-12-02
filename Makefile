NAME = philo

DIR_SRC = ./SRC/
DIR_OBJ = ./OBJ/
DIR_INC = ./Include/

SRC = main.c\
		philos.c\
		utils.c\
		philo_routine.c\
		monitoring.c\

CFLAGS = -g -Wall -Werror -Wextra

CC = gcc

CLEAN = rm -rf

OBJS := $(SRC:%.c=$(DIR_OBJ)%.o)

all: $(NAME)

$(OBJS): $(DIR_OBJ)%.o: $(DIR_SRC)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@ -I $(DIR_INC)
	@echo "Creando la carpeta $(DIR_OBJ)\nCreando archivos .o"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "Creando el ejecutable: $(NAME)"

clean:
	@echo "Eliminando archivos .o"
	@$(CLEAN) $(DIR_OBJ)

fclean: clean
	@echo "Eliminando el ejecutable: $(NAME)"
	@$(CLEAN) $(NAME)

re: fclean all
.PHONY: all clean fclean