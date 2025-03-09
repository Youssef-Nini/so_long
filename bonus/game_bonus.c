/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:30:22 by ynini             #+#    #+#             */
/*   Updated: 2025/02/28 22:07:52 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
	if (game->map[new_y][new_x] == 'E')
	{
		if (game->collectibles == 0)
			exit_game(game);
		else
			return ;
	}
	if (game->map[new_y][new_x] == 'N')
		exit_game(game);
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_y = new_y;
	game->player_x = new_x;
	game->moves++;
	draw_map(game->map, game);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 13)
		move_player(game, 0, -1);
	else if (keycode == 0)
		move_player(game, -1, 0);
	else if (keycode == 1)
		move_player(game, 0, 1);
	else if (keycode == 2)
		move_player(game, 1, 0);
	else if (keycode == 53)
		exit_game(game);
	else
		return (0);
	return (0);
}

void	draw_map(char **map, t_game *game)
{
	int		x;
	int		y;
	void	*img;

	img = NULL;
	y = 0;
	while (map[y])
	{
		x = 0;
		put_img_to_win(game, x, y, img);
		y++;
	}
	display_moves(game);
}

void	game_img(t_game *game)
{
	int	w;
	int	h;

	game->player_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/player.xpm", &w, &h);
	game->floor_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/floor.xpm", &w, &h);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/exit.xpm", &w, &h);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/wall.xpm", &w, &h);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx, \
	"textures/collectible.xpm", &w, &h);
	if (!game->player_img || !game->floor_img || !game->exit_img \
	|| !game->wall_img || !game->collectible_img)
		exit_game(game);
}

void	the_game(char **map)
{
	t_game	game;
	int		*coords;

	game.mlx = mlx_init();
	check_fail(game.mlx, map);
	game.win = mlx_new_window(game.mlx, 48 * ft_strlen(map[0]), \
	48 * calc_rows(map), "the game");
	check_fail(game.win, map);
	game.map = map;
	game.collectibles = calc_character(map, 'C');
	coords = find_coordinate(map, 'P');
	game.player_x = coords[1];
	game.player_y = coords[0];
	free(coords);
	game.moves = 0;
	game_img(&game);
	game.enemy_frame = 0;
	game.frame_counter = 0;
	load_enemy_img(&game);
	store_enemies(&game);
	draw_map(map, &game);
	mlx_loop_hook(game.mlx, update_enemy, &game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
}
