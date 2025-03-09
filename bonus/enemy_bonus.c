/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:32:23 by ynini             #+#    #+#             */
/*   Updated: 2025/02/27 17:55:18 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_flags(t_game *game)
{
	if (!game->enemy_img[0] || !game->enemy_img[1] || !game->enemy_img[2] \
	|| !game->enemy_img[3] || !game->enemy_img[4] || !game->enemy_img[5] \
	|| !game->enemy_img[6] || !game->enemy_img[7] || !game->enemy_img[8] \
	|| !game->enemy_img[9])
		exit_game(game);
}

void	load_enemy_img(t_game *game)
{
	int	w;
	int	h;

	game->enemy_img[0] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_1.xpm", &w, &h);
	game->enemy_img[1] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_2.xpm", &w, &h);
	game->enemy_img[2] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_3.xpm", &w, &h);
	game->enemy_img[3] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_4.xpm", &w, &h);
	game->enemy_img[4] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_5.xpm", &w, &h);
	game->enemy_img[5] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_6.xpm", &w, &h);
	game->enemy_img[6] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_7.xpm", &w, &h);
	game->enemy_img[7] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_8.xpm", &w, &h);
	game->enemy_img[8] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_9.xpm", &w, &h);
	game->enemy_img[9] = mlx_xpm_file_to_image(game->mlx, \
	"textures/enmy_10.xpm", &w, &h);
	check_flags(game);
}

void	draw_enemy(t_game *game, int i)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->enemy_img[game->enemies[i].frame],
		game->enemies[i].x * 48, game->enemies[i].y * 48);
}

int	update_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (game->enemies[i].frame_counter++ > 5)
		{
			game->enemies[i].frame = (game->enemies[i].frame + 1) % 10;
			game->enemies[i].frame_counter = 0;
		}
		i++;
	}
	i = 0;
	while (i < game->enemy_count)
	{
		draw_enemy(game, i);
		i++;
	}
	return (0);
}

void	store_enemies(t_game *game)
{
	int	x;
	int	y;

	game->enemy_count = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N')
			{
				game->enemies[game->enemy_count].x = x;
				game->enemies[game->enemy_count].y = y;
				game->enemies[game->enemy_count].frame = 0;
				game->enemies[game->enemy_count].frame_counter = 0;
				game->enemy_count++;
			}
			x++;
		}
		y++;
	}
}
