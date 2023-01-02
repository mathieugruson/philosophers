NAME = philo

CC = gcc -g -pthread -fsanitize=thread
FLAGS = -Wall -Wextra -Werror

SRC =	philo.c \
		parsing.c \
		init.c \
		time.c \
		free.c \
		stop_dinner.c


OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : 	$(OBJ)
			 $(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) -c $^

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re