/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:33:20 by ynini             #+#    #+#             */
/*   Updated: 2025/02/28 21:40:03 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	is_rectangular(char *str, char **map)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if ((str[i] == '\n' && str[i] == str[i + 1]) || str[0] == '\n')
			return (write(1, "Error\nEmpty Line\n", 17), 1);
		i++;
	}
	i = 0;
	while (map[i + 1])
	{
		if (ft_strlen(map[i]) != ft_strlen(map[i + 1]))
			return (write(2, "Error\nmap isn't rectangular.\n", 30), 1);
		i++;
	}
	if (ft_strlen(map[0]) > 53 || calc_rows(map) > 29)
		return (write(1, "Error\nThe map is big for the screen.\n", 37), 1);
	return (0);
}

int	is_wall_exist(char **map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (map[len])
		len++;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[0][j] != '1' || map[len - 1][j] != '1' || map[i][0] != '1' \
			|| (map[i][j + 1] == '\0' && map[i][j] != '1'))
				return (write(1, "Error\nThe map must be closed by walls\n", \
				39), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_char_valid(char **map)
{
	int	i;
	int	j;
	int	num_char[127];

	i = 0;
	ft_bzero(num_char, sizeof(num_char));
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' && \
			map[i][j] != 'E' && map[i][j] != 'P' && map[i][j] != 'N')
				return (write(1, "Error\nThe map has an invalid character.\n", \
				40), 1);
			num_char[(unsigned char)map[i][j]]++;
			j++;
		}
		i++;
	}
	if (num_char['E'] != 1 || num_char['C'] == 0 || \
	num_char['P'] != 1 || num_char['N'] == 0)
		return (write(1, \
		"Error\nCheck the characters.\n", 28), 1);
	return (0);
}

int	flood_fill(char **map, int x, int y, int rows)
{
	int	cols;
	int	collectible;
	int	result;

	cols = ft_strlen(map[0]);
	result = 0;
	collectible = 0;
	if (x < 0 || y < 0 || x >= cols || y >= rows || map[y][x] == '1'\
	|| map[y][x] == 'N')
		return (0);
	if (map[y][x] == 'E')
		return (map[y][x] = '1', 1);
	if (map[y][x] == 'C')
		collectible++;
	map[y][x] = '1';
	result = flood_fill(map, x + 1, y, rows) + \
	flood_fill(map, x - 1, y, rows) + \
	flood_fill(map, x, y + 1, rows) + \
	flood_fill(map, x, y - 1, rows);
	return (collectible + result);
}

int	is_path_valid(char **map)
{
	int		rows;
	int		*coor_p;
	int		collectible;
	char	**map_copy;
	int		res;

	rows = calc_rows(map);
	coor_p = find_coordinate(map, 'P');
	collectible = calc_character(map, 'C');
	map_copy = copy_map(map, rows);
	if (!map_copy)
		return (0);
	res = flood_fill(map_copy, coor_p[1], coor_p[0], rows);
	if (res < collectible + 1)
		write (1, "Error\ncheck The path.\n", 22);
	free_arr(map_copy, rows);
	free(coor_p);
	return (!(res == collectible + 1));
}
