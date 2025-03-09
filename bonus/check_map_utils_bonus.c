/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:38:32 by ynini             #+#    #+#             */
/*   Updated: 2025/02/26 09:13:50 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*arr;

	arr = (unsigned char *)s;
	while (n--)
		*arr++ = 0;
}

int	*find_coordinate(char **map, int c)
{
	int	i;
	int	j;
	int	*coord;

	i = 0;
	j = 0;
	coord = malloc(sizeof(int *) * 2);
	if (!coord)
		return (NULL);
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == c)
			{
				coord[0] = j;
				coord[1] = i;
				return (coord);
			}
			i++;
		}
		j++;
	}
	return (coord);
}

int	calc_character(char **map, int c)
{
	int	i;
	int	j;
	int	num_character;

	i = 0;
	j = 0;
	num_character = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == c)
				num_character++;
			i++;
		}
		j++;
	}
	return (num_character);
}

int	calc_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	**copy_map(char **map, int rows)
{
	char	**map_copy;
	int		j;

	j = 0;
	map_copy = malloc(sizeof(char *) * rows + 1);
	if (!map_copy)
		return (NULL);
	while (j < rows)
	{
		map_copy[j] = ft_strdup(map[j]);
		if (!map_copy[j])
			return (free_arr(map_copy, j - 1), NULL);
		j++;
	}
	map_copy[j] = NULL;
	return (map_copy);
}
