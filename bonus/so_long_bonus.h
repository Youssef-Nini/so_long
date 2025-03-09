/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:40:32 by ynini             #+#    #+#             */
/*   Updated: 2025/03/03 12:46:15 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "get_next_line_bonus.h"
# include "ft_printf_bonus.h"

typedef struct s_enemy
{
	int		x;
	int		y;
	int		frame;
	int		frame_counter;
}	t_enemy;

typedef struct s_game
{
	void	*mlx;
	void	*win;

	char	**map;
	int		player_x;
	int		player_y;

	int		collectibles;
	int		moves;

	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	void	*collectible_img;
	void	*exit_img;

	void	*enemy_img[10];
	t_enemy	enemies[1500];
	int		enemy_count;
	int		enemy_frame;
	int		frame_counter;
}	t_game;

size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
void	free_arr(char **arr, int len);

//Check_Map
int		is_rectangular(char *str, char **map);
int		is_wall_exist(char **map);
int		is_char_valid(char **map);
int		flood_fill(char **map, int x, int y, int rows);
int		is_path_valid(char **map);

//Check_Map_Utils
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		*find_coordinate(char **map, int c);
int		calc_character(char **map, int c);
int		calc_rows(char **map);
char	**copy_map(char **map, int rows);

//The_Game
void	move_player(t_game *game, int dx, int dy);
int		handle_keypress(int keycode, t_game *game);
void	draw_map(char **map, t_game *game);
void	the_game(char **map);
void	free_game(t_game *game);
void	exit_game(t_game *game);
int		close_game(t_game *game);
void	display_moves(t_game *game);
void	put_img_to_win(t_game *game, int x, int y, void *img);
void	check_fail(void *ptr, char **map);

//The_Enemy
void	load_enemy_img(t_game *game);
void	draw_enemy(t_game *game, int i);
int		update_enemy(t_game *game);
void	store_enemies(t_game *game);

#endif