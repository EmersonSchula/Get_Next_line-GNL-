NAME = get_next_line

CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g3

SRC = 	get_next_line.c\
		get_next_line_utils.c\
		main.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

gdb: $(NAME)
	gdb -tui ./$(NAME)

get_next_line.o: get_next_line.h
get_next_line_utils.o: get_next_line.h

.PHONY: all clean fclean re

#gcc -Wall -Wextra -Werror -g3 get_next_line.c get_next_line_utils.c main.c -o get_next_line 
#valgrind --leak-check=full --show-leak-kinds=all ./a.out