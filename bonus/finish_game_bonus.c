/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_game_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:31:41 by ynini             #+#    #+#             */
/*   Updated: 2025/02/28 22:01:42 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_game(t_game *game)
{
	free_arr(game->map, calc_rows(game->map));
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	mlx_destroy_window(game->mlx, game->win);
}

void	exit_game(t_game *game)
{
	free_game(game);
	exit(0);
}

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
}

void	check_fail(void *ptr, char **map)
{
	if (!ptr)
		return (free_arr(map, calc_rows(map)), exit(1));
}
