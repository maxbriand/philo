NAME = philo
CC = cc
FLAGS = -Wall -Werror -Wextra

SRC = main.c
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
