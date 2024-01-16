NAME = philo
FLAGS = -Wall -Wextra -Werror
SRC = src/
INC = inc/
CC = cc
CC_FLAGS = -c -I $(INC)
C_FILES = main.c initialize.c restaurant.c utils.c death_monitoring.c
O_FILES = $(C_FILES:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $(O_FILES) -o $(NAME)

%.o: $(SRC)%.c $(INC)philo.h
	$(CC) $(FLAGS) $(CC_FLAGS) $< -o $@

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
