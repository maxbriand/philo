NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra

SRC = 	main.c \
		src/ft_exe.c \
		src/ft_parsing.c \
		src/ft_perror.c \
		src/ft_utils.c \
		src/ft_set_strucs.c \
		src/ft_free_all.c \
		src/ft_die_check.c \
		src/ft_states.c \
		src/ft_meal.c \

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

valgrind:
	valgrind --tool=drd --tool=helgrind ./philo 3 200 200 200

.PHONY: all re fclean clean
