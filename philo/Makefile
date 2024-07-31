NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra

SRC = 	main.c \
		src/ft_exe.c \
		src/ft_parsing.c \
		src/ft_utils.c \
		src/ft_set_config.c \
		src/ft_free_all.c \
		src/ft_end_check.c \
		src/ft_meal.c \
		src/ft_atol.c \
		src/ft_utils2.c \
		src/ft_set_philos.c \

OBJ = $(patsubst %.c, %.o, $(SRC))

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -g -c $< -o $@ -Iinclude

clean:
	@rm -f *.o
	@rm -f src/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re fclean clean
