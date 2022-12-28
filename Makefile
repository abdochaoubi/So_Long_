CC = gcc
SRC = mandatory/so_long.c mandatory/so_long_hook.c  utils/ft_putnbr.c utils/ft_putstr.c utils/ft_strncmp.c ./getsky/lol.c ./getsky/lol_3.c ./getsky/lol_2.c ./getsky/get_next_line.c ./getsky/get_next_line_utils.c utils/ft_itoa.c utils/ft_split.c
B_SRC = bonus/so_long_bonus.c bonus/so_long_bonus_2.c bonus/so_long_bonus_3.c bonus/so_long_bonus_1.c  utils/ft_strncmp.c  utils/ft_putnbr.c utils/ft_putstr.c ./getsky/lol.c ./getsky/lol_3.c ./getsky/lol_2_bonus.c ./getsky/get_next_line.c ./getsky/get_next_line_utils.c utils/ft_itoa.c utils/ft_atoi.c utils/ft_split.c
NAME = so_long
NAME_BONUS = so_long_bonus
Flags = -Wall -Wextra -Werror

%.o: %.c
	$(CC) -c $(Flags)  -o $@ $<

OBJ = $(SRC:%.c=%.o)

B_OBJ = $(B_SRC:%.c=%.o)

$(NAME): $(OBJ)
	$(CC)  $(Flags) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) 

all: $(NAME)

$(NAME_BONUS):$(B_OBJ)   
	$(CC) $(Flags) $(B_OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	rm -rf $(OBJ) $(B_OBJ)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

norm:
	norminette bonus getsky mandatory utils