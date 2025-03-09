NAME = so_long
NAME_BONUS = so_long_bonus

CFLAGS = -Wall -Wextra -Werror

OBJ = so_long.o get_next_line.o get_next_line_utils.o help_fc.o ft_split.o \
check_map.o check_map_utils.o ft_printf.o ft_putchar.o ft_putstr.o ft_putnbr.o \
game.o finish_game.o

OBJ_BONUS = bonus/so_long_bonus.o bonus/get_next_line_bonus.o bonus/get_next_line_utils_bonus.o bonus/help_fc_bonus.o bonus/ft_split_bonus.o \
bonus/check_map_bonus.o bonus/check_map_utils_bonus.o bonus/ft_printf_bonus.o bonus/ft_putchar_bonus.o bonus/ft_putstr_bonus.o bonus/ft_putnbr_bonus.o \
bonus/game_bonus.o bonus/finish_game_bonus.o bonus/enemy_bonus.o bonus/print_moves_bonus.o

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	cc $(CFLAGS) $(OBJ_BONUS) -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS)

bonus/%.o: bonus/%.c bonus/so_long_bonus.h
	cc $(CFLAGS) -c $< -o $@

%.o: %.c so_long.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -rf $(NAME) $(NAME_BONUS)

re: fclean all