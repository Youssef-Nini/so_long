/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynini <ynini@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 08:42:17 by ynini             #+#    #+#             */
/*   Updated: 2025/02/28 21:32:05 by ynini            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_map(char **map, char *lines)
{
	if (!lines)
		return (write(2, "Error\nThe file is empty\n", 24), 1);
	if (lines[ft_strlen(lines) - 1] == '\n')
		return (write(1, "Error\n\\n exist at the end of file.\n", \
		35), free(lines), 1);
	map = ft_split(lines, '\n');
	if (!map)
		return (free(lines), 1);
	if (is_rectangular(lines, map) || is_wall_exist(map) || \
	is_char_valid(map) || is_path_valid(map))
		return (free(lines), free_arr(map, calc_rows(map)), 1);
	free(lines);
	the_game(map);
	return (0);
}

int	read_map(char *file_path)
{
	int		fd;
	char	*line;
	char	*lines;
	char	**map;
	char	*tmp;

	map = NULL;
	fd = open(file_path, O_RDONLY, 0777);
	if (fd == -1)
		return (write(2, "Error\nOpen function faild.\n", 27), 1);
	line = get_next_line(fd);
	lines = ft_strjoin(lines, line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		tmp = lines;
		lines = ft_strjoin(lines, line);
		free(line);
		free(tmp);
	}
	close(fd);
	return (check_map(map, lines));
}

int	parsing(int ac, char **av)
{
	int	len;

	if (ac != 2)
		return (write(1, "Error\nYou need one parameter.\n", 30), 1);
	len = ft_strlen(av[1]);
	if (ft_strncmp(".ber", av[1] + (len - 4), 4) != 0)
		return (write(2, "Error\nThe file doesn't have .ber extension\n", \
		43), 1);
	read_map(av[1]);
	return (0);
}

int	main(int ac, char **av)
{
	if (parsing(ac, av))
		return (1);
}
