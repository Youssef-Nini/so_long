/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_moves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:57:08 by ynini             #+#    #+#             */
/*   Updated: 2025/02/28 21:52:05 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	ft_numlen(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*num;

	nb = n;
	len = ft_numlen(nb);
	num = malloc(len + 1);
	if (!num)
		return (NULL);
	if (nb < 0)
	{
		num[0] = '-';
		nb = -nb;
	}
	num[len] = '\0';
	while (nb > 0)
	{
		num[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n == 0)
		num[0] = '0';
	return (num);
}

void	display_moves(t_game *game)
{
	char	*moves_str;
	char	*display_str;

	moves_str = ft_itoa(game->moves);
	if (!moves_str)
		exit(1);
	display_str = ft_strjoin("Moves: ", moves_str);
	free(moves_str);
	if (display_str)
	{
		mlx_string_put(game->mlx, game->win, 10, 10, 0xFFFFFF, display_str);
		free(display_str);
	}
	else
		exit(1);
}

void	put_img_to_win(t_game *game, int x, int y, void *img)
{
	while (game->map[y][x])
	{
		img = NULL;
		if (game->map[y][x] == '1')
			img = game->wall_img;
		if (game->map[y][x] == 'P')
			img = game->player_img;
		if (game->map[y][x] == 'C')
			img = game->collectible_img;
		if (game->map[y][x] == 'E')
			img = game->exit_img;
		if (game->map[y][x] == '0')
			img = game->floor_img;
		if (img)
			mlx_put_image_to_window(game->mlx, game->win, img, x * 48, y * 48);
		x++;
	}
}
